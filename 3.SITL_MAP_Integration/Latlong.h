/****************************************************************
* Air Bridge Software
* @file Latlong.h
*
* @brief This file implements SITL Integration along with Maps
* 
* @group SITLMapIntegration
* 
* @author Developer
* @version 1.1 10/11/21 
* Change request No: NA
* @Directory  ~/AirBridge/src/FlightMap/MapItems
* HLR ID : TBD
* LLR ID : TBD
*********************************************************************/

#ifndef LATLONG_H
#define LATLONG_H
#include <QTextStream>
#include <QObject>
#include <QString>
#include <QGeoCoordinate>
#include <QMap>
#include <qqml.h>
#include <QJsonObject>
#include <QJsonDocument>
#include <QVariant>
#include <QFile>


// Class to inherit from QObject for QT Rendering

class Latlong  : public QObject
{
    Q_OBJECT
public:
    Latlong(QObject* parent = nullptr);
    ~Latlong();

    // Q_PROPERTY and Q_INVOKABLE for SITL mapping

    Q_PROPERTY(int currentPlanViewVIIndex  READ currentPlanViewVIIndex  NOTIFY currentPlanViewVIIndexChanged)
    Q_INVOKABLE int insertSimpleMissionItem(QGeoCoordinate coordinate, int visualItemIndex);
    Q_INVOKABLE int saveJSON();

    QMap<int, QGeoCoordinate> mapPoints;
    QJsonObject json;

    int currentPlanViewVIIndex(void) const
    {
        return _currentPlanViewVIIndex;
    }

signals:
    void currentPlanViewVIIndexChanged (QMap<int, QGeoCoordinate>,int);

private:
    int _currentPlanViewVIIndex = 0;

};

#endif // LATLONG_H
