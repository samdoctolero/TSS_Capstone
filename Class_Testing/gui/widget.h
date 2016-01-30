#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setName(const QString &name);
    QString name() const;
    void setTime(const QString &time);
    void setTemperature(const QString &temp);
    void setPower(const QString &power);
    void setBusRouteInfo(const QString &busRouteNumber, const QString &stopsNumber, const QString &timeSince);
    void displayBusRouteInfo();
private:
    Ui::Widget *ui;
     QStandardItemModel* busList;
      QStandardItemModel* stopsList;
       QStandardItemModel* timeList;
};

#endif // WIDGET_H
