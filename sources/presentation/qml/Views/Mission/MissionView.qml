import QtQuick 2.6
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

import "qrc:/Controls"

Pane {
    id: root

    MissionMapView {
        objectName: "map"
        anchors.fill: parent
    }
}
