#include "guishelter.h"
#include "ui_guishelter.h"

guiShelter::guiShelter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::guiShelter)
{
    ui->setupUi(this);
    this->showFullScreen();
    ui->lbl_logo->setPixmap(QPixmap("C:\\Users\\Sam\\Documents\\TSS_Capstone\\images\\coc_logo.jpeg"));
    //ui->lbl_logo.setPixmap("C:\\Users\\Sam\\Documents\\TSS_Capstone\\images\\coc_logo.jpeg");
    ui->lbl_logo->show();

}

guiShelter::~guiShelter()
{
    delete ui;
}

