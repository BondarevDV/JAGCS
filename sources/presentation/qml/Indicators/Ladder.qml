import QtQuick 2.0
import "qrc:/JS/helper.js" as Helper

Rectangle {
    id: root

    property alias value: label.value
    property int minValue: 0
    property int maxValue: 100
    property int valueStep: 20
    property int fontPixelSize: palette.fontPixelSize * 0.7
    property alias canvasRotation: canvas.rotation

    property alias prefix: label.prefix
    property color scaleColor: palette.textColor

    property bool vertical: (canvasRotation >= 90 && canvasRotation < 180) ||
                            (canvasRotation <= -90 && canvasRotation > -180)

    color: palette.sunkenColor
    clip: true
    onValueChanged: canvas.requestPaint()
    onScaleColorChanged: canvas.requestPaint()

    Canvas {
        id: canvas
        anchors.centerIn: parent
        width: vertical ? parent.height : parent.width
        height: vertical ? parent.width : parent.height
        onPaint: {
            var ctx = canvas.getContext('2d');

            ctx.clearRect(0, 0, width, height);

            ctx.save();
            ctx.beginPath();

            ctx.lineWidth = 2;
            ctx.strokeStyle = scaleColor;
            ctx.fillStyle = scaleColor;
            ctx.font = fontPixelSize + 'px sans-serif';
            ctx.textAlign = vertical ?
                        (canvasRotation > 0 ? 'right' : 'left') : 'center';
            ctx.textBaseline = vertical ? 'middle' : 'top';

            var counter = 0;
            for (var i = minValue - (minValue % valueStep); i <= maxValue;
                 i += (valueStep / 2)) {
                var major = (counter++ % 2) == 0;
                var xPos = canvasRotation > 0 ?
                            width - Helper.mapToRange(i, minValue, maxValue, width) :
                            Helper.mapToRange(i, minValue, maxValue, width);
                ctx.moveTo(xPos, 0);
                ctx.lineTo(xPos, major ? fontPixelSize * 0.5 : fontPixelSize * 0.25);
                if (major) {
                    ctx.save();
                    ctx.translate(xPos, fontPixelSize * 0.65);
                    ctx.rotate(-canvasRotation * Math.PI / 180);
                    ctx.fillText(i, 0, 2);
                    ctx.restore();
                }
            }

            ctx.stroke();
            ctx.restore();
        }
    }

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width
        height: label.height
        color: palette.raisedColor

        FdLabel {
            id: label
            anchors.centerIn: parent
            width: parent.width
            color: scaleColor
        }
    }
}