import QtQuick 2.7


Item {
    id: root

    property string text
    signal clicked
    
    Text {
        text: root.text
        color: "#fff"
        opacity: ma.containsPress ? 1 :
                 ma.containsMouse ? 0.75 : 0.5
        anchors.verticalCenter: parent.verticalCenter
    }

    MouseArea{
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
    }
}