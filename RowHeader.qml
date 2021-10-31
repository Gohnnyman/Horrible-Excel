import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

TableView {
    property int cellWidth: 0
    property int cellHeight: 0
    property color cellColor: "yellow"
    property alias model: repeater.model
    id: rowHeader
    syncDirection: Qt.Vertical
    Column {
        anchors.fill: parent
        Repeater {
            id: repeater
            Rectangle {
                width: cellWidth
                height: cellHeight
                border.width: 1
                color: cellColor
                TextEdit {
                    text: modelData
                }
            }
        }
    }
}
