/****************************************************************
* Air Bridge Software
* @file OrderController.cc
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

#include "OrderController.h"

OrderController::OrderController(QObject *parent) : QObject(parent)
{

}

void OrderController::setpickuppoint(QGeoCoordinate pickuppoint)
{
    if (pickuppoint != _pickuppoint) {
        _pickuppoint = pickuppoint;
        emit pickuppointChanged();
        qDebug()<<"Pickup position longitude is :"<< pickuppoint.longitude();
        qDebug()<<"Pickup position latitude is :"<< pickuppoint.latitude();
    }
}

void OrderController::setdroppoint(QGeoCoordinate droppoint)
{
    if (droppoint != _droppoint) {
        _droppoint = droppoint;
        emit droppointChanged();
        emit orderidChanged();
        qDebug()<<"Drop position longitude is : "<< droppoint.longitude();
        qDebug()<<"Drop position latitude is : "<< droppoint.latitude();
    }
}
void OrderController::setorderid(int orderid)
{

    if (orderid != _orderid) {
        _orderid = orderid;
    emit orderidChanged();
        qDebug()<<"Order ID is :"<<orderid;
    }
}
