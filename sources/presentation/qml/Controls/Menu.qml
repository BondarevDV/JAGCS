import QtQuick 2.6
import QtQuick.Controls 2.2 as T

T.Menu {
    id: control

    background: Rectangle {
        implicitWidth: sizings.controlBaseSize * 6
        implicitHeight: sizings.controlBaseSize
        color: customPalette.raisedColor

        Shadow {
            visible: !control.flat
            source: parent
        }
    }
}
