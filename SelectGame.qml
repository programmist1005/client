import QtQuick 2.6
import QtQuick.Controls 2.4
import game 1.0
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

    Image {
        width: parent.width/16
        height: parent.height/16
        source: Pieces.Back
        MouseArea {
            anchors.fill: parent
            onClicked: loader.source = "MainWindow.qml"
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
        id: newGame
        text: qsTr("New game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.bottom: createGame.top
        anchors.bottomMargin: board.height/4
        onClicked:{
            game.setPlayerNumber(0)
            loader.source = "Game.qml"
        }
    }

    Button {
        id: createGame
        text: qsTr("Create game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        anchors.centerIn: parent
        onClicked: loader.source = "PortServer.qml"
    }

    Button {
        id: connectToGame
        text: qsTr("Connect")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.topMargin: board.height/4
        anchors.top: createGame.bottom
        onClicked: loader.source = "PortClient.qml"

    }

    Loader {
        id: loader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
