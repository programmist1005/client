import QtQuick 2.6
import QtQuick.Controls 2.4
import mainClient 1.0
import "pieces.js" as Pieces

Rectangle {
    width: parent.width
    height: parent.height
    color: "BurlyWood"

    Board {
        id: board
    }

    MainClient {
        id: mainClient
    }

    Image {
        width: parent.width/16
        height: parent.height/16
        source: Pieces.Back
        MouseArea {
            anchors.fill: parent
            onClicked: loader.source = "SelectGame.qml"
        }
    }

    Image {
        id: closeGame
        width: parent.width/16
        height: parent.height/16
        source: Pieces.Close
        x: parent.width - closeGame.width
        MouseArea {
            anchors.fill: parent
            onClicked: close()
        }
    }

    Button {
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.bottom: textInput.top
        anchors.bottomMargin: board.height/4
        text: qsTr("Enter port")
        font.pixelSize: board.height/16
    }

    Rectangle {
        id:  textInput
        width: parent.width/2
        height: parent.height/10
        anchors.centerIn: parent
        color: "#F4F2F5"
        border.color: "gray"
        border.width: 1

        TextInput {
            id: portInput
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: TextInput.AlignHCenter
            verticalAlignment: TextInput.AlignVCenter
            font.pixelSize: board.height/16
            width: parent.width
            cursorVisible: true
        }
    }

    Button {
        text: qsTr("Start game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.topMargin: board.height/4
        anchors.top: textInput.bottom
        onClicked:{
            if( portInput.text>999 ){
                mainClient.setPortNumber(portInput.text)
                loader.source = "NewGame.qml"
                game.setPlayerNumber(2)
            }
        }
    }

    Loader {
        id: loader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
