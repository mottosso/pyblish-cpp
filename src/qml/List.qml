import QtQuick 2.7
import QtQuick.Controls 2.1


ListView {
    ScrollBar.vertical: ScrollBar {}

    section.delegate: SectionDelegate {
        text: section
        height: 20
        width: 100
    }

    interactive: false
    displayMarginBeginning: 50
    displayMarginEnd: 50
    pixelAligned: true
}
