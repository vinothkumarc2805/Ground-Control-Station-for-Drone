/****************************************************************
* Air Bridge Software
*
* @file OrderView.qml
*
* @brief This file implements UI for Order view. This file is temporary and willl be
*   used till the interface received from other application
*
*@group AirBridge
*
*@author Author
*
*@file directory /AirBridge/OrderView.qml
*
* @version 1.1 25/11/2021
*
* Change request No: NA
*
* HLR ID : TBD
* LLR ID : TBD
*********************************************************************/
//start
import QtQuick 2.0
import QtQuick          2.3
import QtQuick.Controls 1.2
import QtQuick.Dialogs  1.2

import QtLocation       5.3
import QtPositioning    5.3
import QtQuick.Layouts  1.2
import QtQuick.Window   2.2

import QGroundControl                   1.0
import QGroundControl.FlightMap         1.0
import QGroundControl.ScreenTools       1.0
import QGroundControl.Controls          1.0
import QGroundControl.FactSystem        1.0
import QGroundControl.FactControls      1.0
import QGroundControl.Palette           1.0
import QGroundControl.Controllers       1.0
import QGroundControl.ShapeFileHelper   1.0
import QGroundControl.Airspace          1.0
import QGroundControl.Airmap            1.0
Item{
     id:             orderWindow
     visible:        true
     Rectangle{
         id:orderrectangle
         width:250
         height: 800
         gradient: Gradient {
             GradientStop { position: 0.0; color: "red" }
             GradientStop { position: 0.33; color: "yellow" }
             GradientStop { position: 1.0; color: "green" }
         }

         property bool   _mainWindowIsMap:       mapControl.pipState.state === mapControl.pipState.fullState
         property bool   _isFullWindowItemDark:  _mainWindowIsMap ? mapControl.isSatelliteMap : true
         property var    _activeVehicle:         QGroundControl.multiVehicleManager.activeVehicle
         property var    _missionController:     _planController.missionController
         property var    _geoFenceController:    _planController.geoFenceController
         property var    _rallyPointController:  _planController.rallyPointController
         property real   _margins:               ScreenTools.defaultFontPixelWidth / 2
         property var    _guidedController:      guidedActionsController
         property var    _guidedActionList:      guidedActionList
         property var    _guidedAltSlider:       guidedAltSlider
         property real   _toolsMargin:           ScreenTools.defaultFontPixelWidth * 0.75
         property rect   _centerViewport:        Qt.rect(0, 0, width, height)
         property real   _rightPanelWidth:       ScreenTools.defaultFontPixelWidth * 30
         property var    _mapControl:            mapControl

         property real   _fullItemZorder:    0
         property real   _pipItemZorder:     QGroundControl.zOrderWidgets

         function _calcCenterViewPort() {
             var newToolInset = Qt.rect(0, 0, width, height)
             toolstrip.adjustToolInset(newToolInset)
             if (QGroundControl.corePlugin.options.instrumentWidget) {
                 flightDisplayViewWidgets.adjustToolInset(newToolInset)
             }
         }

         QGCToolInsets {
             id:                     _toolInsets1
             leftEdgeBottomInset:    _pipOverlay.visible ? _pipOverlay.x + _pipOverlay.width : 0
             bottomEdgeLeftInset:    _pipOverlay.visible ? parent.height - _pipOverlay.y : 0
         }
         ColumnLayout{
             Button{
                 id: addWaypointRallyPointAction1
                 text:"FROM"
                 checkable: true
                 onClicked:  {

                 }
             }
             QGCLabel {
                 text:           qsTr("Press the button to confirm your pickup address")
                 font.pointSize: ScreenTools.smallFontPointSize
             }
             Button{
                 id:                 addWaypointRallyPointAction2
                 text:               qsTr("TO")
                 checkable:          true
             }

             QGCLabel {
                 text:           qsTr("Press the button to select your delivery address")
                 font.pointSize: ScreenTools.smallFontPointSize
             }
             Text{
                 text:"Order ID"
                 font.pixelSize: 30
                 font.bold: true
                 font.italic: true
             }
             TextField{
                 id:orderid
             }
         }
         Button{
             text:"ORDER"
             y:400
             onClicked:
                 orderWindow.visible=false
         }

         Rectangle{
             width: 1500
             height: 1500
             anchors.left: orderrectangle.right
             Item {
                 id:             panel1
                 anchors.fill:   parent

                 FlightMap {
                     id:                         editorMap1
                     anchors.fill:               parent
                     mapName:                    "MissionEditor"
                     allowGCSLocationCenter:     true
                     allowVehicleLocationCenter: true
                     planView:                   true

                     zoomLevel:                  QGroundControl.flightMapZoom
                     center:                     QGroundControl.flightMapPosition

                     // Initial map position duplicates Fly view position
                     Component.onCompleted: editorMap1.center = QGroundControl.flightMapPosition

                     QGCMapPalette { id: mapPal1; lightColors: editorMap1.isSatelliteMap }

                     onZoomLevelChanged: {
                         QGroundControl.flightMapZoom = zoomLevel
                         updateAirspace(false)
                     }
                     onCenterChanged: {
                         QGroundControl.flightMapPosition = center
                         updateAirspace(false)
                     }
                     Repeater {
                         model: _missionController.visualItems
                         delegate: MissionItemMapVisual {
                             map:        editorMap1
                             onClicked:  _missionController.setCurrentPlanViewSeqNum(sequenceNumber, false)
                             opacity:    editingLayer == layerMission ? 1 : editorMap1._nonInteractiveOpacity
                             interactive: editingLayer == layerMission
                         }
                     }

                     MouseArea {
                         anchors.fill: parent
                         onClicked: {
                             // Take focus to close any previous editing
                             editorMap1.focus = true
                             var coordinate = editorMap1.toCoordinate(Qt.point(mouse.x, mouse.y), false /*clipToViewPort*/)
                             coordinate.latitude = coordinate.latitude.toFixed(_decimalPlaces)
                             coordinate.longitude = coordinate.longitude.toFixed(_decimalPlaces)
                             coordinate.altitude = coordinate.altitude.toFixed(_decimalPlaces)
                             switch (_editingLayer) {

                             case _layerMission:
                                 if (addWaypointRallyPointAction1.checked) {
                                     insertSimpleItemAfterCurrent(coordinate)
                                 }
                                 else if (_addROIOnClick) {
                                     insertROIAfterCurrent(coordinate)
                                     _addROIOnClick = false
                                 }
                                 break
                             case _layerMission:
                                 if(addWaypointRallyPointAction2.checked){
                                     insertSimpleItemAfterCurrent(coordinate)}
                                 break
                             case _layerRallyPoints:
                                 if (_rallyPointController.supported && addWaypointRallyPointAction1.checked) {
                                     _rallyPointController.addPoint(coordinate)
                                 }
                                 break
                             }
                         }
                     }
                     MapScale {
                         id:                     mapScale1
                         anchors.margins:       100
                         mapControl:             editorMap1
                         buttonsOnLeft:          true
                     }
                 }

             }
         }
     }

 }

//end
