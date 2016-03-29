#include <QApplication>
#include "widget.h"
#include <QPalette>
#include <unistd.h>
#include "Shelter.h"


int main(int argc, char *argv[])
{


    QApplication a(0, 0);
    Widget w;
    w.setCursor(Qt::BlankCursor);
    QPalette pal = a.palette();
    pal.setColor(QPalette::Window, Qt::black);
    a.setPalette(pal);



    w.setTime(12,0);    // use A or P
    w.setTemperature(12);
    w.setPower("000");

    w.displayBusRouteInfo();
    w.showFullScreen();     // calll this on update


    return a.exec();
}
