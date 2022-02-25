/****************************************************************
* Air Bridge Software
* @file OrderController.h
*
* @brief The file implements the Order controller functionalities
* that inteface with the QML Orderview and Flyview components.
*
*
* @group MissionManager
*
* @author Developer
* @version 1.1 20/01/2022
* Change request No: NA
* @Directory  ~/AirBridge/src/MissionManager
* HLR ID : TBD
* LLR ID : TBD
*********************************************************************/

#ifndef ORDERCONTROLLER_H
#define ORDERCONTROLLER_H

#include <QObject>
#include <QGeoCoordinate>

#include "PlanElementController.h"

class OrderController : public QObject
{
    Q_OBJECT
public:
    explicit OrderController(QObject *parent = nullptr);

    Q_PROPERTY(QGeoCoordinate   pickuppoint  READ pickuppoint WRITE setpickuppoint NOTIFY pickuppointChanged)
    Q_PROPERTY(QGeoCoordinate   droppoint  READ droppoint WRITE setdroppoint NOTIFY droppointChanged)
    Q_PROPERTY(int   orderid  READ orderid WRITE setorderid NOTIFY orderidChanged)

    Q_INVOKABLE void  setpickuppoint(QGeoCoordinate pickuppoint);
    Q_INVOKABLE void  setdroppoint(QGeoCoordinate droppoint);
    Q_INVOKABLE void  setorderid(int orderid);

    QGeoCoordinate pickuppoint(void) const
    {
        return _pickuppoint;
    }
    QGeoCoordinate droppoint(void) const
    {
        return _droppoint;
    }
    int orderid(void) const
    {
        return _orderid;
    }


signals:
    void pickuppointChanged();
    void droppointChanged();
    void orderidChanged();


private:
    QGeoCoordinate   _pickuppoint;
    QGeoCoordinate   _droppoint;
    int   _orderid = 0;

};

#endif // ORDERCONTROLLER_H
