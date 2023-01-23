import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import SaveUser 1.0

Button {
    id: myButton

    width: 100
    height: 50
    contentItem: Text {
        anchors.centerIn: parent
        text: "myButton.text"
        color: myButton.pressed ? "#c8c378" : "black"
    }

    background: Rectangle {
        color: myButton.pressed ? "transparent" : "transparent"
        border.color: myButton.pressed ? "lightgreen" : "black"
        border.width: 2
        radius: 5
    }

}
