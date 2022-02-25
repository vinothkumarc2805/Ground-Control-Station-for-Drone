/****************************************************************
* Air Bridge Software
* @file TakeoffMissionItem.h
*
* @brief The file implements the Take off point support for 
* Launch Location display/editing which is tied to Pickup position
*  
* 
* @group MissionManager
* 
* @author Developer
* @version 1.1 05/01/2022 
* Change request No: NA
* @Directory  ~/AirBridge/src/MissionManager
* HLR ID : TBD
* LLR ID : TBD
*********************************************************************/

#pragma once

#include "SimpleMissionItem.h"
#include "MissionSettingsItem.h"

class PlanMasterController;

/// Takeoff mission item is a special case of a SimpleMissionItem which supports Launch Location display/editing
/// which is tied to home position.
class TakeoffMissionItem : public SimpleMissionItem
{
    Q_OBJECT
    
public:
    TakeoffMissionItem(PlanMasterController* masterController, bool flyView, MissionSettingsItem* settingsItem, bool forLoad, QObject* parent);
    TakeoffMissionItem(MAV_CMD takeoffCmd, PlanMasterController* masterController, bool flyView, MissionSettingsItem* settingsItem, QObject* parent);
    TakeoffMissionItem(const MissionItem& missionItem,  PlanMasterController* masterController, bool flyView, MissionSettingsItem* settingsItem, QObject* parent);

    Q_PROPERTY(QGeoCoordinate   launchCoordinate            READ launchCoordinate               WRITE setLaunchCoordinate               NOTIFY launchCoordinateChanged)
    Q_PROPERTY(bool             launchTakeoffAtSameLocation READ launchTakeoffAtSameLocation    WRITE setLaunchTakeoffAtSameLocation    NOTIFY launchTakeoffAtSameLocationChanged)

    QGeoCoordinate  launchCoordinate            (void) const { return _settingsItem->coordinate(); }
    bool            launchTakeoffAtSameLocation (void) const { return _launchTakeoffAtSameLocation; }

    void setLaunchCoordinate            (const QGeoCoordinate& launchCoordinate);
    void setLaunchTakeoffAtSameLocation (bool launchTakeoffAtSameLocation);

    static bool isTakeoffCommand(MAV_CMD command);

    ~TakeoffMissionItem();

    // Overrides from VisualMissionItem
    void            setCoordinate           (const QGeoCoordinate& coordinate) override;
    bool            isTakeoffItem           (void) const final { return true; }
    double          specifiedFlightSpeed    (void) final { return std::numeric_limits<double>::quiet_NaN(); }
    double          specifiedGimbalYaw      (void) final { return std::numeric_limits<double>::quiet_NaN(); }
    double          specifiedGimbalPitch    (void) final { return std::numeric_limits<double>::quiet_NaN(); }
    QString         mapVisualQML            (void) const override { return QStringLiteral("TakeoffItemMapVisual.qml"); }

    // Overrides from SimpleMissionItem
    bool load(QTextStream &loadStream) final;
    bool load(const QJsonObject& json, int sequenceNumber, QString& errorString) final;

    //void setDirty(bool dirty) final;

signals:
    void launchCoordinateChanged            (const QGeoCoordinate& launchCoordinate);
    void launchTakeoffAtSameLocationChanged (bool launchTakeoffAtSameLocation);

private:
    void _init(bool forLoad);
    void _initLaunchTakeoffAtSameLocation(void);

    MissionSettingsItem*    _settingsItem;
    bool                    _launchTakeoffAtSameLocation = true;
};
