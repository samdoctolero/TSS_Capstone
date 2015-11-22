#include "guishelter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    guiShelter w;
    w.show();

    return a.exec();
}
