import QtQuick 2.9

TextInput {
    id: root

    onActiveFocusChanged: if (activeFocus) selectAll()

    horizontalAlignment: Qt.AlignHCenter
    font.pixelSize: sizings.primaryFontSize
    color: customPalette.textColor
    selectionColor: customPalette.selectionColor
    selectedTextColor: customPalette.selectedTextColor
}
