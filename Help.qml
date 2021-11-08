import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    title: qsTr("Допомога")

    minimumWidth: 820
    maximumWidth: 820
    minimumHeight: 550
    maximumHeight: 550
    modality: Qt.Dialog
    flags: Qt.Dialog

    Flickable {
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent
        anchors.margins: 10
        contentHeight: column.implicitHeight
//        contentWidth: ColumnLayout.implicitWidth
        ColumnLayout
        {
            id: column
            anchors.fill: parent
            Text {
                text: "Хлопчик, дівчинка чи ще хтось вводить якусь строку в клітинку."
            }

            Image {
                Layout.alignment: Qt.AlignCenter
                source: "img/1.png"
            }

            Text {
                text: "Після чого може ссилатися на цю комірку з іншої комірки.
Але не слід забувати, що всі обчіслення вкінці приводяться до типу bool.

Обічислення відбуваються за стандартом ECMAScript Edition 4, окрім таких операцій:
    == -> =
    ! -> not
    max -> max (для 2 аргументів)
    mmax -> max (для більше 2 аргументів)
Тому з любим питанням, що стосується синтаксису, звертатися до документації ECMAScript.

Щоб вписати в комірку формулу, слід спочатку написати '=', а потім вже саму формулу: "
            }

            Image {
                Layout.alignment: Qt.AlignCenter
                source: "img/2.png"
            }

            Text {
                text: "Як бачите, ми ввели 1+1=2 і відповідью стало true, і це вірно.

В принципі, це все що потрібно було б сказати, якби не силки. А робляться вони ось так: "
            }

            Image {
                Layout.alignment: Qt.AlignCenter
                source: "img/3.png"
            }

            Text {
                text: "Звісно, виникла помилка. А це все тому, що якщо ми взяли значення з комірки
'kria', а ECMAScript просто підставляє її в свій код і не розуміє синтаксиса що ми написали.
А от якщо зробимо так, то все спрацює: "
            }

            Image {
                Layout.alignment: Qt.AlignCenter
                source: "img/4.png"
            }

            Text {
                text: "Якщо потрібно добавити комірки, то просто нажміть на одну з цих
чарівних кнопочок: "
            }

            Image {
                Layout.alignment: Qt.AlignCenter
                source: "img/5.png"
            }

            Text {
                text: "Щасти!"
            }
        }
    }
}
