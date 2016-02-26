#include "widget.h"
#include "ui_widget.h"
#include <QStandardItem>
#include <QPalette>
#include <QLCDNumber>

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

}

Widget::~Widget()
{
    delete ui;
}


void Widget::setTime(const QString &time) {
    ui->TimeDisplay->display(time);
}
void Widget::setTemperature(const QString &temp) {
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
