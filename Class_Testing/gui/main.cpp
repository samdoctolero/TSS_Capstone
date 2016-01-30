#include <QApplication>
#include "widget.h"
#include <QPalette>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setCursor(Qt::BlankCursor);
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, Qt::black);
    a.setPalette(pal);



    w.setTime("12:00A");    // use A or P
    w.setTemperature("12C");
    w.setPower("123");

    w.setBusRouteInfo("1","2","3");
    w.setBusRouteInfo("4","5","6");
    w.setBusRouteInfo("7","8","9");
     w.setBusRouteInfo("10","11","12");

    w.displayBusRouteInfo();
    w.showFullScreen();     // calll this on update

    return a.exec();
}
