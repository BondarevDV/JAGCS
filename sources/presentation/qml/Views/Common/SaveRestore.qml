import QtQuick 2.6
import QtQuick.Layouts 1.3

import "qrc:/Controls" as Controls

GridLayout {
    id: root

    property alias message: messageLabel.text
    property alias backgroundColor: frame.backgroundColor

    signal save()
    signal restore()

    columns: 2
    rowSpacing: sizings.spacing
    columnSpacing: sizings.spacing

    Controls.Frame {
        id: frame
        backgroundColor: customPalette.cautionColor
        visible: message.length > 0
        padding: sizings.padding
        Layout.preferredHeight: messageLabel.implicitHeight + padding * 2
        Layout.fillWidth: true
        Layout.preferredWidth: 0
        Layout.columnSpan: 2

        Controls.Label {
            id: messageLabel
            color: customPalette.selectedTextColor
            horizontalAlignment: Text.AlignHCenter
            elide: Text.ElideNone
            wrapMode: Text.WordWrap
            anchors.fill: parent
        }
    }

    Controls.Button {
        text: qsTr("Restore")
        iconSource: "qrc:/icons/restore.svg"
        onClicked: restore()
        Layout.fillWidth: true
    }

    Controls.Button {
        text: qsTr("Save")
        iconSource: "qrc:/icons/save.svg"
        onClicked: save()
        Layout.fillWidth: true
    }
}
