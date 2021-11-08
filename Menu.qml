import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    title: qsTr(" ")
    width: 300; height: 250
    maximumWidth: 300
    maximumHeight: 250
    minimumWidth: 300
    modality: Qt.Dialog
    flags: Qt.Dialog


    ColumnLayout {
        anchors.margins: 20
        anchors.fill: parent
        anchors.centerIn: parent

        Text {
            Layout.alignment: Qt.AlignCenter
            text: "Меню"
        }


        Button {

            id: returnButton
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            text: "Повернутися"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.close();
                }
            }
        }

        Button {
            id: saveButton
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            text: "Зберегти"
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.saveFile();
                    root.close();
                }
            }
        }

        Button {
            id: openButton
            text: "Відкрити"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    ExcelTable.openFile();
                    root.close();
                }
            }
        }

        Button {
            id: infoButton
            text: "Інформація"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var component = Qt.createComponent("Info.qml")
                    var window = component.createObject(root)
                    window.show()
                }
            }
        }

        Button {
            id: helpButton
            text: "Допомога"
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var component = Qt.createComponent("Help.qml")
                    var window = component.createObject(root)
                    window.show()
                }
            }
        }
    }
}
