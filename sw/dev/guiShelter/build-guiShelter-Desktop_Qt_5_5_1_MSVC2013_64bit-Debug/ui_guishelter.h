/********************************************************************************
** Form generated from reading UI file 'guishelter.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUISHELTER_H
#define UI_GUISHELTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiShelter
{
public:
    QWidget *centralWidget;
    QGraphicsView *graphicsView;
    QLCDNumber *lcdNumber;
    QLabel *label;
    QLabel *label_2;
    QLCDNumber *lcdNumber_2;
    QLabel *label_3;
    QLabel *label_4;
    QLCDNumber *lcdNumber_3;
    QLabel *label_5;
    QLabel *lbl_logo;

    void setupUi(QMainWindow *guiShelter)
    {
        if (guiShelter->objectName().isEmpty())
            guiShelter->setObjectName(QStringLiteral("guiShelter"));
        guiShelter->setWindowModality(Qt::NonModal);
        guiShelter->resize(593, 316);
        guiShelter->setAutoFillBackground(false);
        guiShelter->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 103);"));
        centralWidget = new QWidget(guiShelter);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 421, 321));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(430, 20, 81, 23));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(520, 20, 71, 16));
        QFont font;
        font.setPointSize(9);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(430, 0, 151, 16));
        label_2->setFont(font);
        lcdNumber_2 = new QLCDNumber(centralWidget);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(430, 60, 81, 23));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(430, 40, 151, 21));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(520, 60, 41, 21));
        label_4->setFont(font1);
        lcdNumber_3 = new QLCDNumber(centralWidget);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(430, 290, 81, 23));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(520, 290, 71, 16));
        label_5->setFont(font);
        lbl_logo = new QLabel(centralWidget);
        lbl_logo->setObjectName(QStringLiteral("lbl_logo"));
        lbl_logo->setGeometry(QRect(430, 90, 151, 81));
        guiShelter->setCentralWidget(centralWidget);

        retranslateUi(guiShelter);

        QMetaObject::connectSlotsByName(guiShelter);
    } // setupUi

    void retranslateUi(QMainWindow *guiShelter)
    {
        guiShelter->setWindowTitle(QApplication::translate("guiShelter", "guiShelter", 0));
        label->setText(QApplication::translate("guiShelter", "Power (kW)", 0));
        label_2->setText(QApplication::translate("guiShelter", "Power Generation Stats", 0));
        label_3->setText(QApplication::translate("guiShelter", "This shelter can power : ", 0));
        label_4->setText(QApplication::translate("guiShelter", "iPhones", 0));
        label_5->setText(QApplication::translate("guiShelter", "* Celsius", 0));
        lbl_logo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class guiShelter: public Ui_guiShelter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUISHELTER_H
