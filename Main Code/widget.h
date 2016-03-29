#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QStandardItemModel>
#include "IR.h"
#include "Ping.h"
#include "RelayBoard.h"
#include "TempHumid.h"
#include "ConfigManager.h"
#include "BusInfo.h"
#include "Solar.h"
#include "Monitor.h"

#define MAX_BUS 10

namespace Ui {
	class Widget;
}

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = 0);
	~Widget();
	void setName(const QString &name);
	QString name() const;
	void setTime(int h, int m);
	void setTemperature(double T);
	void setPower(const QString &power);
	void setBusRouteInfo(int busRouteNumber, int stopsNumber, int timeSince);
private:
	Ui::Widget *ui;

	//Bus info boxes
	QStandardItemModel* busList;
	QStandardItemModel* stopsList;
	QStandardItemModel* timeList;

	//Timer to grab data from the devices
	QTimer * controlTimer;
	QTimer * busDataTimer;
	QDateTime * currTime;
	QTimer * solarDataTimer;

	//Timeout variables
	int controlPollTimeout;
	int busPollTimeout;
	int solarPollTimeout;

	//Devices
	IR * bulbTemp;
	Ping *  proxSensor;
	RelayBoard * bulbControl;
	TempHumid * tempHumid;
	Solar * solarData;
	BusInfo * Bus[MAX_BUS];
	Monitor * screen;

signals:

public slots :
		void control();				//controls screen and heater
		void displayBusRouteInfo();	//refreshes bus information
		void acquireSolarData();	//refreshes solar data
};

#endif // WIDGET_H
