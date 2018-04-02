import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "RadioStatus"
import "Connection"

Item {
    id: topbar

    height: sizings.controlBaseSize

    TopbarPresenter {
        id: presenter
        view: topbar
    }

    RowLayout {
        anchors.left: parent.left
        height: parent.height
        spacing: sizings.spacing

        Controls.Button {
            iconSource: "qrc:/icons/burger.svg"
            tipText: qsTr("Menu")
            flat: true
            onClicked: menu.home()
        }

        Controls.Button {
            iconSource: "qrc:/icons/planning.svg"
            tipText: qsTr("Planning")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Planning/PlanningView.qml", qsTr("Planning"), {})
        }

        Controls.Button {
            iconSource: "qrc:/icons/fleet.svg"
            tipText: qsTr("Vehicles")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Vehicles/VehicleListView.qml", qsTr("Vehicles"), {})
        }

        Controls.Button {
            iconSource: connection.connected ? "qrc:/icons/connect.svg" :
                                               "qrc:/icons/disconnect.svg"
            iconColor: connection.connected ? customPalette.textColor :
                                              customPalette.dangerColor
            tipText: qsTr("Links")
            flat: true
            onClicked: menu.goTo("qrc:/Views/Menu/Links/LinkListView.qml", qsTr("Links"), {})
        }
    }

    RowLayout {
        anchors.right: parent.right
        height: parent.height
        spacing: sizings.spacing

        ConnectionView {
            id: connection
        }

        RadioStatusView {
            id: radioStatus
            Layout.preferredWidth: sizings.controlBaseSize * 5
        }

        Controls.Button {
            iconSource: "qrc:/icons/left.svg"
            tipText: qsTr("Overview")
            enabled: dashboard.selectedVehicle !== undefined
            flat: true
            onClicked: dashboard.selectVehicle(0)
        }

        Controls.Button {
            visible: dashboard.selectedVehicle !== undefined
            iconSource: "qrc:/icons/joystick.svg"
            tipText: (manual.enabled ? qsTr("Disable") : qsTr("Enable")) +
                     " " + qsTr("manual control")
            iconColor: manual.enabled ? customPalette.selectionColor : customPalette.textColor
            flat: true
            onClicked: manual.setEnabled(!manual.enabled)
        }

        Controls.Button {
            iconSource: "qrc:/icons/service.svg"
            tipText: qsTr("Service")
            enabled: !serviceMenu.visible
            flat: true
            onClicked: serviceMenu.open()

            Controls.Menu {
                id: serviceMenu
                y: parent.height

                function addMenuItem(item) {
                    if (serviceMenu.width < item.width) serviceMenu.width = item.width;
                    else item.width = serviceMenu.width;
                    addItem(item);
                }

                function clearMenuItems() {
                    while (contentData.count > 0) removeItem(0);
                }
            }
        }

        Controls.Label {
            text: dashboard.selectedVehicle !== undefined ?
                      dashboard.selectedVehicle.name : qsTr("All MAVs")
            font.bold: true
        }

        Controls.Button {
            iconSource: dashboardVisible ? "qrc:/icons/hide_dashboard.svg" :
                                           "qrc:/icons/show_dashboard.svg"
            tipText: (dashboardVisible ? qsTr("Hide") : qsTr("Show")) +
                     " " + qsTr("dashboard")
            flat: true
            onClicked: dashboardVisible = !dashboardVisible
        }
    }
}
