import QtQuick 2.12
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import SaveUser 1.0
import QtQuick.Layouts 1.3

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")


    function addNetTask(task) {
        taskList.setTask(task)
    }

    SaveUser {
        id: taskList
    }
    MyButton {
        id: myButton
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.bottomMargin: 25
        anchors.rightMargin: 50
        enabled: true
        onClicked: {
            addNetTask(taskEdit.text + " " + date.text + " " + progress.text)
        }
    }

    Rectangle {
        anchors.fill: parent
        z: -2
        gradient: 5
    }
    Rectangle {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 20
        color: "transparent"
        border.color: "black"
        z: -1
        Row {
            id: row
            spacing: 5
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            height: 50
            Rectangle {
                height: parent.height
                width: parent.width/4
                clip: true
                color: "transparent"
                border.color: "black"
                TextField {
                    id:taskEdit
                    placeholderText: "Enter task:"

                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
            Rectangle {
                height: parent.height
                width: parent.width/4
                clip: true
                color: "transparent"
                border.color: "black"
                TextField {
                    id:date
                    placeholderText: "Enter date: dd.mm.yyyy "
                    validator: RegularExpressionValidator { regularExpression: /[0-9]{2}\.[0-9]{2}\.[0-9]{4}/ }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }
            Rectangle {
                height: parent.height
                width: parent.width/4
                clip: true
                color: "transparent"
                border.color: "black"
                TextField {
                    id:progress
                    placeholderText: "Enter progress: 0-10 "
                    validator: RegularExpressionValidator { regularExpression: /[0-9]{1}|[1]{1}[0]{1}/ }
                    background: Rectangle {
                        color: "transparent"
                    }
                }
            }

        }
        ListView {
            id: lv
                ScrollBar.vertical: ScrollBar {
                    active: hovered || pressed
                    hoverEnabled: true
                }
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.bottom: row.top
            spacing: 20
            model: taskList.model
            delegate: Rectangle {
                anchors.right: parent.right
                anchors.left: parent.left
                height: 30
                radius: 15
                color: "transparent"
                border.color: "black"
                Text { text: modelData; anchors.centerIn: parent }
                }
        }
    }
}
