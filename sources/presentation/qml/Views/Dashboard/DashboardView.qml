import QtQuick 2.6
import JAGCS 1.0

import "qrc:/Controls" as Controls

Item {
    id: dashboard

    property var selectedVehicle

    property bool rollInverted: settings.boolValue("Gui/fdRollInverted")
    property int speedStep: settings.value("Gui/fdSpeedStep")
    property int speedUnits: settings.value("Gui/fdSpeedUnits")
    property int altitudeStep: settings.value("Gui/fdAltitudeStep")
    property int altitudeUnits: settings.value("Gui/fdAltitudeUnits")
    property bool altitudeRelative: settings.boolValue("Gui/fdRelativeAltitude")

    property string speedSuffix: units.trSpeedUnits(speedUnits)
    property string altitudeSuffix: units.trDistanceUnits(altitudeUnits)

    function selectVehicle(vehicleId) {
        presenter.selectVehicle(vehicleId);
    }

    function updateDisplay() {
        if (selectedVehicle !== undefined) {
            switch (selectedVehicle.type) {
            case Vehicle.FixedWing:
            case Vehicle.FlyingWing:
            default:
                // TODO: Special displays for special types
                loader.setSource("Displays/AerialVehicleDisplay.qml",
                                 { "vehicleId": selectedVehicle.id });
            }
        }
        else {
            loader.setSource("Displays/VehiclesListDisplay.qml")
        }
    }

    Component.onCompleted: updateDisplay()
    onSelectedVehicleChanged: updateDisplay()

    DashboardPresenter {
        id: presenter
        view: dashboard
    }

    Loader {
        id: loader
        clip: true
        anchors.right: parent.right
        width: parent.width / 2
        height: parent.height
    }
}
