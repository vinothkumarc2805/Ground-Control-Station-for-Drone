/****************************************************************
* Air Bridge Software
* @file CustomMapItems.qml
*
* @brief This file implements SITL Integration along with Maps
*
* @group SITLMapIntegration
*
* @author Developer
* @version 1.1 10/11/21 
* Change request No: NA
* @Directory ~/AirBridge/src/FlightMap/MapItems
* HLR ID : TBD
* LLR ID : TBD
*********************************************************************/

import QtQuick          2.3
import QtLocation       5.3
import QtPositioning    5.3

import QGroundControl           1.0
import QGroundControl.Controls  1.0
import QGroundControl.FlightMap 1.0
import QGroundControl.Vehicle   1.0

// Allowing custom builds to add visual items associated with the Flight Plan to the map


Item {
    property var    map             ///< Map control to show items
    property bool   largeMapView    ///< true: map takes up entire view, false: map is in small window

    Instantiator {
        model: QGroundControl.corePlugin.customMapItems

        Item {
            property var _customObject

            Component.onCompleted: {
                var controlUrl = object.url
                if (controlUrl !== "") {
                    var component = Qt.createComponent(controlUrl);
                    if (component.status === Component.Ready) {
                        _customObject = component.createObject(map, { "customMapObject": object })
                        if (_customObject) {
                            map.addMapItem(_customObject)
                        }
                    } else {
                        console.log("Main SITL Component creation failed", component.errorString())
                    }
                }
            }

            Component.onDestruction: {
                if (_customObject) {
                    _customObject.destroy()
                }
            }
        }
    }
}
