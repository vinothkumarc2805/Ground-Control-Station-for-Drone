/****************************************************************
* Air Bridge Software
* @file Latlong.cc
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

#include <QtGlobal>
#include<QDebug>

#include "Latlong.h"


// Constructor to initiate the parent Object
Latlong::Latlong(QObject *parent)
{
    // No need to initialise any variables
}

// Destructor to destruct the parent Object
Latlong::~Latlong()
{

}

int Latlong::insertSimpleMissionItem(QGeoCoordinate coordinate, int visualItemIndex)
{

    _currentPlanViewVIIndex = visualItemIndex;
    mapPoints[visualItemIndex] = coordinate;
    emit currentPlanViewVIIndexChanged(mapPoints,visualItemIndex); //Signal to emit the Planview index change
    return 0;
}

// Save the Plan to JSON format
int Latlong::saveJSON()
{

    QMapIterator<int, QGeoCoordinate> i(mapPoints);

    {

        i.next();
        json["Number"] = i.key();
        json["Latitude"] = i.value().latitude();
        json["Longitude"] = i.value().longitude();
    }

    QJsonDocument document;
    document.setObject( json );
    QFile file( "mapJSON.txt" );  // This is temporary Location for SITL demonstration
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    if( file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        iStream.setCodec( "utf-8" );
        iStream << bytes;
        file.close();
    }
    else
    {
        qDebug() << "file open failed: " << endl;
    }


    qDebug() << "JSON saved successfully " << endl;
    return 0;
}


