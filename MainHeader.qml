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
            id: menuButton
            text: "Меню"

            onClicked: {
                var component = Qt.createComponent("Menu.qml")
                var window = component.createObject(root)
                window.show()
            }
        }

        Button {
            id: addRowButton
            anchors.left: menuButton.right
            anchors.leftMargin: 10
            text: "Додати рядок"
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
            text: "Додати стовпчик"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.addColumn()
                    columnHeader.model = ExcelTable.getHeader()
                    table.forceLayout()
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
