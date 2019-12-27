import QtQuick 2.6
import QtQuick.Dialogs 1.2
import "pieces.js" as Pieces

Dialog {
    id: blackPiece
    signal signalExit( string newPiece )
    width: mainQML.width/2
    height: mainQML.height/2
    title: qsTr("Select new chess piece")

    Main {
        id: mainQML
    }

    contentItem: Rectangle {
        width: blackPiece.width
        height: blackPiece.height

        Grid {
            rows: 2
            columns: 2

            Rectangle { color: "white"; width: blackPiece.width/2; height: blackPiece.height/2 }
            Rectangle { color: "gray"; width: blackPiece.width/2; height: blackPiece.height/2 }
            Rectangle { color: "gray"; width: blackPiece.width/2; height: blackPiece.height/2 }
            Rectangle { color: "white"; width: blackPiece.width/2; height: blackPiece.height/2 }
        }

        Grid {
            rows: 2
            columns: 2

            Image {
                width: blackPiece.width/2
                height: blackPiece.height/2
                source: Pieces.Black_queen
                MouseArea {
                    anchors.fill: parent
                    onClicked: blackPiece.signalExit(Pieces.Black_queen)
                }
            }

            Image {
                width: blackPiece.width/2
                height: blackPiece.height/2
                source:Pieces.Black_rook
                MouseArea {
                    anchors.fill: parent
                    onClicked: blackPiece.signalExit(Pieces.Black_rook)
                }
            }

            Image {
                width: blackPiece.width/2
                height: blackPiece.height/2
                source: Pieces.Black_knight
                MouseArea {
                    anchors.fill: parent
                    onClicked: blackPiece.signalExit(Pieces.Black_knight)
                }
            }

            Image {
                width: blackPiece.width/2
                height: blackPiece.height/2
                source: Pieces.Black_bishop
                MouseArea {
                    anchors.fill: parent
                    onClicked: blackPiece.signalExit(Pieces.Black_bishop)
                }
            }
        }
    }
}
