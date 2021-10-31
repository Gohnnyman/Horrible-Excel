import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: mainHeader
    property alias headerText: mainEditText
    //        color: "coral"
    Rectangle {
        anchors.margins: 5
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right

        Button {
            id: addRowButton
            text: "Add row"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.addRow()
                    rowHeader.model = ExcelTable.rowCount()
                    table.forceLayout()
                }
            }

        }

        Button {
            id: addColumnButton
            anchors.left: addRowButton.right
            anchors.leftMargin: 10
            text: "Add column"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.addColumn()
                    columnHeader.model = ExcelTable.getHeader()
                    table.forceLayout()
                }
            }
        }

        Button {
            id: saveButton
            anchors.left: addColumnButton.right
            anchors.leftMargin: 10
            text: "Save file"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.saveFile();
                }
            }
        }

        Button {
            id: openButton
            anchors.left: saveButton.right
            anchors.leftMargin: 10
            text: "Open file"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.openFile();
                }
            }
        }

    }



    Rectangle {
        color: "lightgrey"
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 5
        height: 20


        TextEdit {
            id: mainEditText
            anchors.fill: parent
            text: ExcelTable.textEdit
            onTextChanged: {
                ExcelTable.textEdit = mainEditText.text;
                if(activeFocus) {
                    ExcelTable.saveLastCellText();
                    table.forceLayout();
                }
            }

            Keys.onReturnPressed: {
                console.log("Enter pressed")
            }
        }

        MouseArea {
            onClicked: {
                mainEditText.forceActiveFocus();
            }
        }
    }
}
