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
//Devices
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"
#include "Solar.h"
#include "BusInfo.h"

#define POLL_TIME 5000 //5 seconds

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->TemperatureDisplay->setStyleSheet("border: none");
    ui->TimeDisplay->setStyleSheet("border: none");
    ui->PowerDisplay->setStyleSheet("border: none");

    ui->BusRouteList->setStyleSheet("border: none");
    ui->StopsList->setStyleSheet("border: none");
    ui->TimeList->setStyleSheet("border: none");

    busList = new QStandardItemModel();
    stopsList = new QStandardItemModel();
    timeList = new QStandardItemModel()
            ;
    QPalette pal = ui->TemperatureDisplay->palette();
    pal.setColor(pal.WindowText, QColor(255,255,255));
    ui->TemperatureDisplay->setPalette(pal);


     pal = ui->TimeDisplay->palette();
     pal.setColor(pal.WindowText, QColor(255,255,255));

      ui->TimeDisplay->setPalette(pal);

      pal = ui->PowerDisplay->palette();
      pal.setColor(pal.WindowText, QColor(255,255,255));
        ui->PowerDisplay->setPalette(pal);
    //ui->BusRouteList


        //Initialize the devices
        ConfigManager config;
        config.ReadConfigFile();

		//wiringPi creates the connections in the backend
		wiringPiSetup();

        //allocate memory and create new instances
        //of each classes
        bulbTemp = new IR();
        proxSensor =  new Ping(config.ping_control, config.ping_tolerance, config.ping_run_time);
        bulbControl = new RelayBoard(config.relay_control, config.relay_idle_temperature, config.relay_minimum_temperature);
        tempHumid = new TempHumid(config.temp_humid_pin);
        //Set up gui

        //Connect and start the poll timers
        controlTimer = new QTimer(this);
        connect(controlTimer, SIGNAL(timeout()), this,SLOT(control()));
        controlTimer->start(POLL_TIME);

        //
        hdmiOn = true;

        //
        //currTime = new QDateTime();
        //connect(currTime,SIGNAL(timeChanged()), this,SLOT(updateTime()));
}



void Widget::screenSaver(bool obj)
{
    //If an object exists turn on the screen, if it is off
    // otherwise turn if off, if it is on
    //hdmiOn is to avoid flickering screen due to constant turning on of the screen
    if (obj == true)
    {
        if (hdmiOn == false)
        {
            screenOn();
        }
    }
    else
    {
        if (hdmiOn == true)
        {
            screenOff();
        }
    }
}

void Widget::screenOff()
{
    if (system("sudo tvservice -o") != 0)
    {
        std::cout << "Cannot turn OFF HDMI" << std::endl;
    }
    else
    {
        hdmiOn = false;
    }
}

void Widget::screenOn()
{
    if ((system("sudo tvservice -p") != 0) || system("sudo chvt 9 && sudo chvt 7") != 0 )
    {
        std::cout << "Cannot turn ON HDMI" << std::endl;
    }
    else
    {
        hdmiOn = true;
    }const int
}

Widget::~Widget()
{
    delete ui;
    delete bulbTemp;
    delete proxSensor;
    delete bulbControl;
    delete tempHumid;
    delete controlTimer;
}

void Widget::control()
{
    //Get data:
    double bulbT = bulbTemp->readDieTemp();
    double envTemp, envHumid;
    tempHumid->PassTempAndHumid(envTemp,envHumid);
    bool objDetected = proxSensor->ObjectDetected();

    //Show data to the screen:
    cout<<"Room Temperature: "<<envTemp<<endl;
    cout<<"Object detected: "<<objDetected<<endl;
    cout<<"Bulb temperature: "<<bulbT<<const int<endl;
    setTemperature(envTemp);

    QDateTime currTime(QDateTime::currentDateTime());
    int hour = currTime.time().hour();
    int min = currTime.time().minute();
    setTime(hour,min);


    //Heater control algorithm:
    bulbControl->heatControl(bulbT,envTemp,objDetected);

    //Power Saving algorithm:
    screenSaver(objDetected);
    //Reset counter:
    controlTimer->start(POLL_TIME);


}


void Widget::setTime(int h, int m) {
    string ampm = "A";
    if (h > 12)
    {
        h = h -12;
        ampm = "P";
    }
    stringstream convH,convM;
    convH << h;
    string T = convH.str();
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

 void Widget::setBusRouteInfo(const QString &brn, const QString &sn, const QString &ts) {
      QStandardItem* busRouteNumber = new QStandardItem(brn);
      QStandardItem* stopsNumber = new QStandardItem(sn);
      QStandardItem* timeSince = new QStandardItem(ts);

     busList->appendRow(busRouteNumber);

     stopsList->appendRow(stopsNumber);
     timeList->appendRow(timeSince);

 }

 void Widget::displayBusRouteInfo() {
     ui->BusRouteList->setModel(busList);
      ui->TimeList->setModel(timeList);
       ui->StopsList->setModel(stopsList);
 }
