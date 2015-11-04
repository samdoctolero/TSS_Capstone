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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_guiShelter
{
public:
    QWidget *centralWidget;
    QPushButton *exit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *guiShelter)
    {
        if (guiShelter->objectName().isEmpty())
            guiShelter->setObjectName(QStringLiteral("guiShelter"));
        guiShelter->resize(400, 300);
        centralWidget = new QWidget(guiShelter);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        exit = new QPushButton(centralWidget);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(160, 80, 75, 23));
        guiShelter->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(guiShelter);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        guiShelter->setMenuBar(menuBar);
        mainToolBar = new QToolBar(guiShelter);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        guiShelter->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(guiShelter);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        guiShelter->setStatusBar(statusBar);

        retranslateUi(guiShelter);
        QObject::connect(exit, SIGNAL(clicked()), guiShelter, SLOT(close()));

        QMetaObject::connectSlotsByName(guiShelter);
    } // setupUi

    void retranslateUi(QMainWindow *guiShelter)
    {
        guiShelter->setWindowTitle(QApplication::translate("guiShelter", "guiShelter", 0));
        exit->setText(QApplication::translate("guiShelter", "EXIT", 0));
    } // retranslateUi

};

namespace Ui {
    class guiShelter: public Ui_guiShelter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUISHELTER_H
