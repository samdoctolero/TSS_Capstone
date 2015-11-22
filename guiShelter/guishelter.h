#ifndef GUISHELTER_H
#define GUISHELTER_H

#include <QMainWindow>

namespace Ui {
class guiShelter;
}

class guiShelter : public QMainWindow
{
    Q_OBJECT

public:
    explicit guiShelter(QWidget *parent = 0);
    ~guiShelter();

private slots:

private:
    Ui::guiShelter *ui;
};

#endif // GUISHELTER_H
