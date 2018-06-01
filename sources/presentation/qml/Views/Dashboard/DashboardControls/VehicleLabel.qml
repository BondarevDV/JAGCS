import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: control

    property alias name: content.text

    clip: true
    implicitWidth: sizings.controlBaseSize * 3
    implicitHeight: sizings.controlBaseSize

    Controls.ContentItem {
        id: content
        anchors.fill: parent
        text: selectedVehicle !== undefined ? selectedVehicle.name : qsTr("No vehicle")
        iconSource: translator.imageFromVehicleState(vehicle.vehicleState)
        iconColor: {
            switch (vehicle.vehicleState) {
            case Domain.Active: return customPalette.positiveColor;
            case Domain.Standby: return customPalette.textColor;
            case Domain.Boot:
            case Domain.Calibrating: return customPalette.highlightColor;
            case Domain.Emergency: return customPalette.cautionColor;
            case Domain.Critical: return customPalette.dangerColor;
            case Domain.UnknownState:
            default: return customPalette.sunkenColor;

            }
        }
        font.bold: true
        font.pixelSize: sizings.secondaryFontSize
    }

    MouseArea {
        id: area
        height: parent.height
        width: height
        hoverEnabled: true
    }

    Controls.ToolTip {
        visible: area.containsMouse
        text: translator.translateVehicleState(vehicle.vehicleState)
        delay: 1000
    }
}
