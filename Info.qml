import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    title: qsTr("Інформація")
//    width: 400; height: 350
    minimumWidth: 420
    maximumWidth: 420
    minimumHeight: 350
    maximumHeight: 350
    modality: Qt.Dialog
    flags: Qt.Dialog

    Flickable {
        boundsBehavior: Flickable.StopAtBounds
        anchors.fill: parent
        contentHeight: text.implicitHeight
        contentWidth: text.implicitWidth
        Text {
            id: text
            anchors.fill: parent
            text: "Автор проекту Федоровський Олександр, К-27.
    Варіант 53, реалізація операторів:
    1) +, -, *, / (бінарні операції);
    6) max(x,y), mіn(x,y);
    7) mmax(x1,x2,...,xN), mmіn(x1,x2,...,xN) (N>=1);
    8) =, <, >;
    10) not;
    "
        }
    }
}
