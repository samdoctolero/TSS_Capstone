#include "guishelter.h"
#include "ui_guishelter.h"

guiShelter::guiShelter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guiShelter)
{
    ui->setupUi(this);
}

guiShelter::~guiShelter()
{
    delete ui;
}
