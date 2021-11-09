import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    property int cellWidth: 100
    property int cellHeight: 50
    property int headerWidth: 30
    property int headerHeight: 30
    property int mainHeaderHeight: 100

    id: root
    width: 840
    height: 480
    visible: true
    title: qsTr("Excel Table")

    MainHeader {
        id: mainHeader
        anchors.left: parent.left
        anchors.right: parent.right
        border.width: 2
        height: mainHeaderHeight
        z: 5
    }

    Rectangle {
        z: 5
        id: rectangleMem
        width: headerWidth
        height: headerHeight
        border.width: 1
        color: "yellow"
        anchors.top: mainHeader.bottom
    }

    ColumnHeader {
        z: 1
        id: columnHeader
        cellHeight: root.headerHeight
        cellWidth: root.cellWidth
        height: root.headerHeight
        model: ExcelTable.getHeader()
        syncView: table
        anchors.top: mainHeader.bottom
    }


    RowHeader {
        id: rowHeader
        z: 1
        cellHeight: root.cellHeight
        cellWidth: root.headerWidth
        width: root.headerWidth
        model: ExcelTable.rowCount()
        syncView: table
        anchors.top: rectangleMem.bottom
    }


    MainTable {
        id: table
        model: ExcelTable
        cellHeight: root.cellHeight
        cellWidth: root.cellWidth
        //        anchors.fill: parent
        anchors.top: rectangleMem.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
    }

}
