import QtQuick 2.6
import "qrc:/JS/helper.js" as Helper

Item {
    id: rollScale

    property real roll: 0.0
    property real minRoll: -25.0
    property real maxRoll: 25.0
    property real rollStep: 5.0
    property color color: customPalette.textColor
    property real fontPixelSize: height > 0 ? height * 0.1 : 1

    onRollChanged: canvas.requestPaint()
    onMinRollChanged: canvas.requestPaint()
    onMaxRollChanged: canvas.requestPaint()
    onRollStepChanged: canvas.requestPaint()
    onColorChanged: canvas.requestPaint()
    onWidthChanged: canvas.requestPaint()
    onHeightChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.fill: parent
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.lineWidth = 2;
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.textBaseline = 'middle';
            ctx.textAlign = 'center';

            ctx.save();
            ctx.translate(width / 2, height / 2);

            ctx.beginPath();
            for (var i = minRoll - (minRoll % rollStep); i <= maxRoll;
                 i += rollStep) {
                ctx.save();
                ctx.rotate(i * Math.PI / 180);
                ctx.moveTo(0, -height / 2);
                ctx.lineTo(0, -height / 2 + (i == 0 ? fontPixelSize / 2 : fontPixelSize / 4));
                ctx.restore();
            }
            ctx.stroke();

            ctx.save();
            var rotation = Math.max(Math.min(-roll, maxRoll), minRoll);
            ctx.rotate(rotation * Math.PI / 180);

            ctx.beginPath();
            ctx.moveTo(-fontPixelSize / 2,
                       -height / 2 + fontPixelSize / 2);
            ctx.lineTo(0, 2 - height / 2);
            ctx.lineTo(fontPixelSize / 2,
                       -height / 2 + fontPixelSize / 2);
            ctx.stroke();

            ctx.font = 'bold ' + fontPixelSize + 'px "Open Sans"';
            ctx.fillText(isNaN(roll) ? "-" : Math.floor(roll), 0, -height / 2 + fontPixelSize);

            ctx.restore();
            ctx.restore();
        }
    }
}
