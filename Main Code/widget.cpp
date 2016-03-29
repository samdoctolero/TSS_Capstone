#include "widget.h"
#include "ui_widget.h"
#include <QStandardItem>
#include <QPalette>
#include <QLCDNumber>
#include <QTimeEdit>
#include <sstream>

#include <iostream>
#include <wiringPi.h>
#include <stdint.h>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>

#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"
#include "Solar.h"
#include "BusInfo.h"
#include "Monitor.h"

using namespace std;

Widget::Widget(QWidget *parent) :
QWidget(parent),
ui(new Ui::Widget)
{
	//Setup the gui
	ui->setupUi(this);
	ui->TemperatureDisplay->setStyleSheet("border: none");
	ui->TimeDisplay->setStyleSheet("border: none");
	ui->PowerDisplay->setStyleSheet("border: none");

	ui->BusRouteList->setStyleSheet("border: none");
	ui->StopsList->setStyleSheet("border: none");
	ui->TimeList->setStyleSheet("border: none");

	//Bus information list
	busList = new QStandardItemModel();
	stopsList = new QStandardItemModel();
	timeList = new QStandardItemModel();

	//Temperature display box
	QPalette pal = ui->TemperatureDisplay->palette();
	pal.setColor(pal.WindowText, QColor(255, 255, 255));
	ui->TemperatureDisplay->setPalette(pal);

	pal = ui->TimeDisplay->palette();
	pal.setColor(pal.WindowText, QColor(255, 255, 255));

	//Time display box
	ui->TimeDisplay->setPalette(pal);

	//Power displaybox
	pal = ui->PowerDisplay->palette();
	pal.setColor(pal.WindowText, QColor(255, 255, 255));
	ui->PowerDisplay->setPalette(pal);

	//Include the logo
	QPixmap pix("TSS_Logo.JPG");
	ui->photoLabel->setPixmap(pix);


	//Initialize the devices
	ConfigManager config;
	config.ReadConfigFile();

	//wiringPi creates the connections in the backend
	wiringPiSetup();

	//allocate memory and create new instances for each class
	bulbTemp = new IR();
	proxSensor = new Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
	bulbControl = new RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
	tempHumid = new TempHumid(config.temp_humid_pin);
	solarData = new Solar(9600);
	for (int i = 0; i < MAX_BUS; i++)
	{
		if (config.busInfo[i].num != -1)
		{
			Bus[i] = new BusInfo(config.busInfo[i].num, config.busInfo[i].id);
		}
		else
		{
			Bus[i] = NULL;
		}
	}

	screen = new Monitor(true, config.monitor_enabled);

	controlPollTimeout = config.control_timeout;
	busPollTimeout = config.bus_timeout;
	solarPollTimeout = config.solar_timeout;

	//Connect and start the poll timers
	controlTimer = new QTimer(this);
	connect(controlTimer, SIGNAL(timeout()), this, SLOT(control()));
	controlTimer->start(controlPollTimeout);

	busDataTimer = new QTimer(this);
	connect(busDataTimer, SIGNAL(timeout()), this, SLOT(displayBusRouteInfo()));
	busDataTimer->start(busPollTimeout);

	solarDataTimer = new QTimer(this);
	connect(solarDataTimer, SIGNAL(timeout()), this, SLOT(acquireSolarData()));
	solarDataTimer->start(solarPollTimeout);
}

Widget::~Widget()
{
	delete ui;
	delete bulbTemp;
	delete proxSensor;
	delete bulbControl;
	delete tempHumid;
	delete controlTimer;
	delete solarData;
	delete[] Bus;
	delete screen;
}

void Widget::control()
{
	//Get data:
	double bulbT = bulbTemp->readDieTemp();
	double envTemp, envHumid;
	tempHumid->PassTempAndHumid(envTemp, envHumid);
	bool objDetected = proxSensor->ObjectDetected();

	//Show data to the screen:
	cout << "Room Temperature: " << envTemp << endl;
	cout << "Object detected: " << objDetected << endl;
	cout << "Bulb temperature: " << bulbT << endl;
	setTemperature(envTemp);


	//Get the current time and update the display time
	QDateTime currTime(QDateTime::currentDateTime());
	int hour = currTime.time().hour();
	int min = currTime.time().minute();
	setTime(hour, min);


	//Heater control algorithm:
	bulbControl->heatControl(bulbT, envTemp, objDetected);

	//Power Saving algorithm:
	screen->control(objDetected);

	//Reset counter:
	controlTimer->start(controlPollTimeout);


}

void Widget::setTime(int h, int m) {
	string ampm = "A";
	if (h > 12)
	{
		h = h - 12;
		ampm = "P";
	}
	stringstream convH, convM;
	convH << h;
	string T = convH.str();
	if (m < 10)
	{
		convM << 0;
	}
	convM << m;
	T.append(":");
	T.append(convM.str());
	T.append(ampm);
	ui->TimeDisplay->display(QString::fromStdString(T));
}

void Widget::setTemperature(double envTemp) {
	stringstream conv;
	conv << envTemp;
	string T = conv.str();
	T.append("C");
	QString temp = QString::fromStdString(T);
	ui->TemperatureDisplay->display(temp);
}

void Widget::setPower(const QString &power) {
	ui->PowerDisplay->display(power);
}

void Widget::displayBusRouteInfo()
{
	busList->clear();
	timeList->clear();
	stopsList->clear();
	for (int i = 0; i< MAX_BUS; i++)
	{
		if (Bus[i] == NULL)break;
		//cout<<"Inside display Bus Route Info"<<endl;
		Bus[i]->updateData();
		int num = Bus[i]->getBusNum();
		QStandardItem * bNum = new QStandardItem(QString::number(num));
		busList->appendRow(bNum);
		int tNow = (unsigned)time(NULL);
		int dtime = abs(tNow - Bus[i]->getTimestamp()) / 60;
		if (dtime > 60)
		{
			dtime = 60;
		}
		QString space = QString("   ");
		if (dtime >= 10)
		{
			space = QString("  ");
		}
		QStandardItem * tDtime = new QStandardItem(space + QString::number(dtime) + QString(" min"));
		timeList->appendRow(tDtime);
		space = QString("      ");
		if (Bus[i]->getNumStopAway() >= 10)
		{
			space = QString("     ");
		}
		QStandardItem * numStop = new QStandardItem(space + QString::number(Bus[i]->getNumStopAway()));
		stopsList->appendRow(numStop);
	}
	// cout<<busList->rowCount()<<endl;
	ui->BusRouteList->setModel(busList);
	ui->TimeList->setModel(timeList);
	ui->StopsList->setModel(stopsList);
	ui->StopsList->show();
	ui->TimeList->show();
	ui->BusRouteList->show();
	busDataTimer->start(busPollTimeout);
}

void Widget::acquireSolarData()
{
	solarData->updateData();
	ui->pb_battPercent->setValue(solarData->getBattPercent());
	ui->PowerDisplay->display(solarData->getPowerUsed());
	cout << "Battery Voltage: " << solarData->getBattVoltage() << " Battery Percentage: " << solarData->getBattPercent() << endl;
	solarDataTimer->start(solarPollTimeout);
}
