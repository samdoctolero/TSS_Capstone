/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Fri Jan 8 01:09:02 2016
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QLabel *label_6;
    QListView *TimeList;
    QGridLayout *gridLayout_2;
    QLCDNumber *PowerDisplay;
    QLabel *label_3;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QListView *BusRouteList;
    QGridLayout *gridLayout_4;
    QLabel *label_5;
    QListView *StopsList;
    QGridLayout *gridLayout;
    QLCDNumber *TimeDisplay;
    QLCDNumber *TemperatureDisplay;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1082, 698);
        Widget->setAutoFillBackground(false);
        gridLayout_6 = new QGridLayout(Widget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setPointSize(36);
        label_6->setFont(font);
        label_6->setTextFormat(Qt::AutoText);
        label_6->setScaledContents(true);

        gridLayout_5->addWidget(label_6, 0, 0, 1, 1);

        TimeList = new QListView(Widget);
        TimeList->setObjectName(QString::fromUtf8("TimeList"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush2(QColor(0, 0, 128, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush2);
        TimeList->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(72);
        TimeList->setFont(font1);
        TimeList->setAutoScroll(false);
        TimeList->setProperty("showDropIndicator", QVariant(false));
        TimeList->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout_5->addWidget(TimeList, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        PowerDisplay = new QLCDNumber(Widget);
        PowerDisplay->setObjectName(QString::fromUtf8("PowerDisplay"));
        PowerDisplay->setAutoFillBackground(false);
        PowerDisplay->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(PowerDisplay, 0, 0, 1, 1);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setScaledContents(true);

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_2, 1, 2, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);
        label_4->setScaledContents(true);

        gridLayout_3->addWidget(label_4, 0, 0, 1, 3);

        BusRouteList = new QListView(Widget);
        BusRouteList->setObjectName(QString::fromUtf8("BusRouteList"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Highlight, brush2);
        BusRouteList->setPalette(palette1);
        BusRouteList->setFont(font1);
        BusRouteList->viewport()->setProperty("cursor", QVariant(QCursor(Qt::BlankCursor)));
        BusRouteList->setLayoutDirection(Qt::LeftToRight);
        BusRouteList->setStyleSheet(QString::fromUtf8(""));
        BusRouteList->setLineWidth(0);
        BusRouteList->setAutoScroll(false);
        BusRouteList->setProperty("showDropIndicator", QVariant(false));
        BusRouteList->setSelectionMode(QAbstractItemView::NoSelection);
        BusRouteList->setSelectionBehavior(QAbstractItemView::SelectItems);
        BusRouteList->setTextElideMode(Qt::ElideMiddle);
        BusRouteList->setLayoutMode(QListView::SinglePass);
        BusRouteList->setUniformItemSizes(true);

        gridLayout_3->addWidget(BusRouteList, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setScaledContents(true);

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        StopsList = new QListView(Widget);
        StopsList->setObjectName(QString::fromUtf8("StopsList"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Highlight, brush2);
        StopsList->setPalette(palette2);
        StopsList->setFont(font1);
        StopsList->setAutoScroll(false);
        StopsList->setProperty("showDropIndicator", QVariant(false));
        StopsList->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout_4->addWidget(StopsList, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_4, 0, 1, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        TimeDisplay = new QLCDNumber(Widget);
        TimeDisplay->setObjectName(QString::fromUtf8("TimeDisplay"));
        TimeDisplay->setMinimumSize(QSize(399, 0));
        QFont font2;
        font2.setPointSize(24);
        TimeDisplay->setFont(font2);
        TimeDisplay->setStyleSheet(QString::fromUtf8(""));
        TimeDisplay->setNumDigits(6);

        gridLayout->addWidget(TimeDisplay, 0, 0, 1, 1);

        TemperatureDisplay = new QLCDNumber(Widget);
        TemperatureDisplay->setObjectName(QString::fromUtf8("TemperatureDisplay"));
        TemperatureDisplay->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(TemperatureDisplay, 1, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout, 1, 0, 1, 1);

        gridLayout_6->setRowStretch(0, 2);
        gridLayout_6->setRowStretch(1, 1);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:48pt; font-weight:600; text-decoration: underline; color:#ffffff;\">Time Since</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:24pt; font-weight:600; color:#ffffff;\">Power Generated</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:48pt; font-weight:600; text-decoration: underline; color:#ffffff;\">Bus Route</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "<html><head/><body><p align=\"center\"><span style=\" font-size:48pt; font-weight:600; text-decoration: underline; color:#ffffff;\">Number of Stops</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
