import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1

Window {
    visible: true
    width: 450
    height: 600
    title: "Pyblish"
    color: "#333"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 2
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            Layout.margins: 2
            color: "#444"
            border.color: "#222"
            border.width: 1
            z: 1
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 2
            color: "#444"
            border.color: "#222"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 4

                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    model: controller.instanceModel
                    delegate: Text {
                        text: model.name
                        width: parent.width
                        color: "white"
                        height: 20
                    }
                }
                ListView {
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    model: controller.pluginModel
                    delegate: Text {
                        text: model.name
                        width: parent.width
                        color: "white"
                        height: 20
                    }
                }
            }
        }

    }
}
