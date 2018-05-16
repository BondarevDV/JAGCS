#ifndef QML_TYPES_H
#define QML_TYPES_H

// Internal
#include "vehicle.h"
#include "link_description.h"
#include "mission.h"
#include "mission_assignment.h"
#include "mission_item.h"
#include "video_source.h"
#include "vehicle_types.h"
#include "command.h"
#include "log_message.h"

#include "manual_controller.h"

#include "topbar_presenter.h"
#include "radio_status_presenter.h"
#include "notifications_presenter.h"
#include "connection_presenter.h"
#include "location_map_presenter.h"
#include "active_video_presenter.h"
#include "dashboard_presenter.h"
#include "vehicles_list_display_presenter.h"
#include "aerial_vehicle_display_presenter.h"
#include "drawer_presenter.h"
#include "link_list_presenter.h"
#include "link_presenter.h"
#include "link_edit_presenter.h"
#include "vehicle_list_presenter.h"
#include "vehicle_presenter.h"
#include "log_list_presenter.h"
#include "planning_presenter.h"
#include "mission_list_presenter.h"
#include "mission_presenter.h"
#include "mission_edit_presenter.h"
#include "mission_item_list_presenter.h"
#include "mission_item_presenter.h"
#include "mission_item_edit_presenter.h"
#include "mission_assignment_presenter.h"
#include "database_presenter.h"
#include "gui_settings_presenter.h"
#include "joystick_settings_presenter.h"
#include "map_settings_presenter.h"
#include "network_settings_presenter.h"
#include "video_source_list_presenter.h"
#include "video_source_presenter.h"
#include "about_presenter.h"

// Qt
#include <QCoreApplication>
#include <QQmlEngine>

using namespace presentation;

static void registerTypes()
{
    qmlRegisterUncreatableType<dto::Vehicle>(
                "JAGCS", 1, 0, "Vehicle", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::LinkDescription>(
                "JAGCS", 1, 0, "LinkDescription", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::Mission>(
                "JAGCS", 1, 0, "Mission", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::MissionAssignment>(
                "JAGCS", 1, 0, "MissionAssignment", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::MissionItem>(
                "JAGCS", 1, 0, "MissionItem", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::Command>(
                "JAGCS", 1, 0, "Command", "Can't create entities in QML");
    qmlRegisterUncreatableType<dto::VideoSource>(
                "JAGCS", 1, 0, "VideoSource", "Can't create entities in QML");
    qmlRegisterUncreatableType<domain::LogMessage>(
                "JAGCS", 1, 0, "LogMessage", "Can't create log messages in QML");

    qmlRegisterUncreatableMetaObject(domain::vehicle::staticMetaObject, "JAGCS", 1, 0, "Domain",
                                     "Can't create enums in QML");

    qmlRegisterUncreatableType<domain::ManualController>(
                "JAGCS", 1, 0, "ManualController", "Can't create ManualController in QML");

    qmlRegisterType<TopbarPresenter>("JAGCS", 1, 0, "TopbarPresenter");
    qmlRegisterType<RadioStatusPresenter>("JAGCS", 1, 0, "RadioStatusPresenter");
    qmlRegisterType<NotificationsPresenter>("JAGCS", 1, 0, "NotificationsPresenter");
    qmlRegisterType<ConnectionPresenter>("JAGCS", 1, 0, "ConnectionPresenter");
    qmlRegisterType<LocationMapPresenter>("JAGCS", 1, 0, "MapPresenter");
    qmlRegisterType<ActiveVideoPresenter>("JAGCS", 1, 0, "ActiveVideoPresenter");
    qmlRegisterType<DashboardPresenter>("JAGCS", 1, 0, "DashboardPresenter");
    qmlRegisterType<VehiclesListDisplayPresenter>("JAGCS", 1, 0, "VehiclesListDisplayPresenter");
    qmlRegisterType<AerialVehicleDisplayPresenter>("JAGCS", 1, 0, "AerialVehicleDisplayPresenter");
    qmlRegisterType<DrawerPresenter>("JAGCS", 1, 0, "DrawerPresenter");
    qmlRegisterType<LinkListPresenter>("JAGCS", 1, 0, "LinkListPresenter");
    qmlRegisterType<LinkPresenter>("JAGCS", 1, 0, "LinkPresenter");
    qmlRegisterType<LinkEditPresenter>("JAGCS", 1, 0, "LinkEditPresenter");
    qmlRegisterType<VehicleListPresenter>("JAGCS", 1, 0, "VehicleListPresenter");
    qmlRegisterType<VehiclePresenter>("JAGCS", 1, 0, "VehiclePresenter");
    qmlRegisterType<LogListPresenter>("JAGCS", 1, 0, "LogListPresenter");
    qmlRegisterType<PlanningPresenter>("JAGCS", 1, 0, "PlanningPresenter");
    qmlRegisterType<MissionListPresenter>("JAGCS", 1, 0, "MissionListPresenter");
    qmlRegisterType<MissionPresenter>("JAGCS", 1, 0, "MissionPresenter");
    qmlRegisterType<MissionEditPresenter>("JAGCS", 1, 0, "MissionEditPresenter");
    qmlRegisterType<MissionItemListPresenter>("JAGCS", 1, 0, "MissionItemListPresenter");
    qmlRegisterType<MissionItemPresenter>("JAGCS", 1, 0, "MissionItemPresenter");
    qmlRegisterType<MissionItemEditPresenter>("JAGCS", 1, 0, "MissionItemEditPresenter");
    qmlRegisterType<MissionAssignmentPresenter>("JAGCS", 1, 0, "MissionAssignmentPresenter");
    qmlRegisterType<DatabasePresenter>("JAGCS", 1, 0, "DatabasePresenter");
    qmlRegisterType<GuiSettingsPresenter>("JAGCS", 1, 0, "GuiSettingsPresenter");
    qmlRegisterType<JoystickSettingsPresenter>("JAGCS", 1, 0, "JoystickSettingsPresenter");
    qmlRegisterType<MapSettingsPresenter>("JAGCS", 1, 0, "MapSettingsPresenter");
    qmlRegisterType<NetworkSettingsPresenter>("JAGCS", 1, 0, "NetworkSettingsPresenter");
    qmlRegisterType<VideoSourceListPresenter>("JAGCS", 1, 0, "VideoSourceListPresenter");
    qmlRegisterType<VideoSourcePresenter>("JAGCS", 1, 0, "VideoSourcePresenter");
    qmlRegisterType<AboutPresenter>("JAGCS", 1, 0, "AboutPresenter");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes)

#endif // QML_TYPES_H
