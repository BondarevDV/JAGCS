import QtQuick 2.6
import QtQuick.Layouts 1.3
import JAGCS 1.0

import "qrc:/Controls" as Controls

import "Missions"

Item {
    id: planning

    property var vehicles: []

    implicitWidth: sizings.controlBaseSize * 11

    PlanningPresenter {
        id: presenter
        view: planning
        Component.onCompleted: updateVehicles()
    }

    Flickable {
        anchors.fill: parent
        anchors.bottomMargin: addRow.height
        contentHeight: Math.max(column.height, frame.height)
        clip: true

        Controls.ScrollBar.vertical: Controls.ScrollBar {}

        Controls.Frame {
            id: frame
            visible: missionList.missionIds.count === 0
            width: parent.width
            height: label.height + sizings.margins * 2

            Controls.Label {
                id: label
                text: qsTr("No items present")
                width: parent.width
                anchors.centerIn: parent
                horizontalAlignment: Text.AlignHCenter
            }
        }

        ColumnLayout {
            id: column
            width: parent.width
            anchors.centerIn: parent
            spacing: sizings.spacing

            MissionListView {
                id: missionList
            }
        }
    }

    RowLayout {
        id: addRow
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: sizings.spacing

        Controls.Button {
            text: qsTr("Add Mission")
            iconSource: "qrc:/icons/add.svg"
            onClicked: missionList.addMission()
            Layout.fillWidth: true
        }

        // TODO: add Area, add Survey
    }
}
