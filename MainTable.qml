import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

TableView {
    property int cellWidth: 0
    property int cellHeight: 0

    id: table
    leftMargin: headerWidth
    columnSpacing: 0
    rowSpacing: 0
    interactive: false
    reuseItems: false

    // for scrolling
    ScrollBar.vertical: ScrollBar {
        id: verticalscrollBar
        anchors.top: table.top
        stepSize: 0.01

    }

    ScrollBar.horizontal: ScrollBar {
        id: horizontalscrollBar
        stepSize: 0.01
    }

    MouseArea {
        anchors.fill: parent
        onWheel: {
            if(wheel.modifiers & Qt.AltModifier) {

                if(wheel.angleDelta.x < 0)
                    horizontalscrollBar.increase();
                else
                    horizontalscrollBar.decrease();
            }
            else
            {
                if(wheel.angleDelta.y < 0)
                    verticalscrollBar.increase();
                else
                    verticalscrollBar.decrease();
            }
        }
    }

    delegate: Rectangle {
        id: cell
        border.color: "black"
        implicitWidth: cellWidth
        implicitHeight: cellHeight
        TextEdit {
            id: cellTextEdit
            anchors.fill: parent
            text: activeFocus ? ExcelTable.textEdit : cellText
            padding: 2
            wrapMode: TextEdit.Wrap
            clip: true

            Component.onDestruction: {
                if(activeFocus) ExcelTable.saveToCell(row, column, text);
            }

            onTextChanged: {
                if(activeFocus) {
                    ExcelTable.saveToCell(row, column, text);
                    ExcelTable.textEdit = cellTextEdit.text;
                }
            }

            onEditingFinished: {
                ExcelTable.saveToCell(row, column, text);
                text = activeFocus ? ExcelTable.textEdit : cellText
                cell.border.width = 1;
            }
        }

        MouseArea {
            id: mousearea
            anchors.fill: parent
            onClicked: {
                table.forceLayout();
                ExcelTable.selectCell(row, column);
                ExcelTable.textEdit = rawCellText;
                mainHeader.headerText.forceActiveFocus();
                mainHeader.headerText.cursorPosition = mainHeader.headerText.length;
            }


        }
    } //Rectangle

} //TableView
