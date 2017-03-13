import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1

CheckDelegate {
    id: control
    text: qsTr("CheckDelegate")
    
    checked: true
    hoverEnabled: true

    contentItem: Text {
        leftPadding: control.indicator.width
        bottomPadding: 5
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.3
        color: control.down ? "#aaa" : "#fff"
        elide: Text.ElideRight
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
    }

    indicator: Rectangle {
        implicitWidth: 9
        implicitHeight: 9
        x: 5
        y: 5
        color: "transparent"
        border.color: control.down ? "#aaa" : "#ddd"

        Rectangle {
            anchors.fill: parent
            anchors.margins: 2
            color: control.down ? "#aaa" : "#ddd"
            visible: control.checked
        }
    }

    background: Rectangle {
        anchors.fill: control
        visible: control.down || control.highlighted
        color: control.down ? "#333" : "#eee"
    }
 
}
