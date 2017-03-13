import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1


ApplicationWindow {
    visible: true
    width: 450
    height: 600
    title: "Pyblish"
    color: "#333"

    header: View { height: 50 }
    footer: View { height: 50 }

    View {        
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            clip: true

            anchors.fill: parent
            anchors.margins: 1

            List {
                id: instanceView

                section.property: "family"

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 5

                model: controller.instanceModel
                delegate: Check {
                    text: model.name
                    width: instanceView.width
                    height: 18
                }
            }

            List {
                id: pluginView

                section.property: "type"

                Layout.fillHeight: true
                Layout.fillWidth: true
                Layout.margins: 5

                model: controller.pluginModel
                delegate: Check {
                    text: model.name
                    width: pluginView.width
                    height: 18
                }
            }
        }
    }

}
