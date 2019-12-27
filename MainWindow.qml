import QtQuick 2.6
import QtQuick.Controls 2.4
import game 1.0

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

    Button {
        id: selectGame
        text: qsTr("Select game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.bottom: continueGame.top
        anchors.bottomMargin: board.height/4
        onClicked: loader.source = "SelectGame.qml"
    }

    Button {
        id: continueGame
        text: qsTr("Сontinue game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        anchors.centerIn: parent
        onClicked:{
            loader.source = "Game.qml"
            game.setPlayerNumber(0)
        }
    }

    Button {
        id: closeGame
        text: qsTr("Close game")
        font.pixelSize: board.height/16
        width: parent.width/2
        height: parent.height/10
        x: parent.width/2 - parent.width/4
        anchors.topMargin: board.height/4
        anchors.top: continueGame.bottom
        onClicked: close()
    }

    Loader {
        id: loader
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
