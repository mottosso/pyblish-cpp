import QtQuick 2.7

Item {
    Rectangle {
        id: outerBorder
        color: "#444"
        border.color: "#222"
        border.width: 1
        anchors.fill: parent
        anchors.margins: 0
   }

    Rectangle {
        id: innerBorder
        color: "transparent"
        border.color: "#555"
        border.width: 1
        anchors.fill: parent
        anchors.margins: 1
    }
}
