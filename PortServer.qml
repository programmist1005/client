import QtQuick 2.6
import QtQuick.Controls 2.4
import game 1.0
import mainClient 1.0
import server 1.0
import "pieces.js" as Pieces

Rectangle {
    width: parent.width
    height: parent.height
    color: "BurlyWood"

    Board {
        id: board
    }

    Game {
        id: game
    }

    MainClient {
        id: mainClient
    }

    Server {
        id: server
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
        anchors.bottom: textArea.top
        anchors.bottomMargin: board.height/4
        text: qsTr("Port №")
        font.pixelSize: board.height/16
    }

    Rectangle {
        id: textArea
        width: parent.width/2
        height: parent.height/10
        anchors.centerIn: parent
        color: "white"
        border.color: "gray"
        border.width: 1

        TextArea {
            id: portArea
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: TextArea.AlignHCenter
            verticalAlignment: TextArea.AlignVCenter
            font.pixelSize: board.height/16
            width: parent.width
            cursorVisible: false
            readOnly: true

            Component.onCompleted:{
                portArea.text = Math.floor((Math.random()*(9999-1000))+1000)
            }
        }
    }

    Button {
        text: qsTr("Start game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.topMargin: board.height/4
        anchors.top: textArea.bottom
        onClicked:{
            server.srartServer(portArea.text)
            mainClient.setPortNumber(portArea.text)
            loader.source = "NewGame.qml"
            game.setPlayerNumber(1)
            game.requestWaitPlayerMove(true)
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
