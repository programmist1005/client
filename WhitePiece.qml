import QtQuick 2.6
import QtQuick.Dialogs 1.2
import "pieces.js" as Pieces

Dialog {
    id: whitePiece
    signal signalExit( string newPiece )
    width: mainQML.width/2
    height: mainQML.height/2
    title: qsTr("Select new chess piece")

    Main {
        id: mainQML
    }

    contentItem: Rectangle {
        width: whitePiece.width
        height: whitePiece.height

        Grid {
            rows: 2
            columns: 2

            Rectangle { color: "white"; width: whitePiece.width/2; height: whitePiece.height/2 }
            Rectangle { color: "gray"; width: whitePiece.width/2; height: whitePiece.height/2 }
            Rectangle { color: "gray"; width: whitePiece.width/2; height: whitePiece.height/2 }
            Rectangle { color: "white"; width: whitePiece.width/2; height: whitePiece.height/2 }
        }

        Grid {
            rows: 2
            columns: 2

            Image {
                width: whitePiece.width/2
                height: whitePiece.height/2
                source: Pieces.White_queen
                MouseArea {
                    anchors.fill: parent
                    onClicked: whitePiece.signalExit(Pieces.White_queen)
                }
            }

            Image {
                width: whitePiece.width/2
                height: whitePiece.height/2
                source: Pieces.White_rook
                MouseArea {
                    anchors.fill: parent
                    onClicked: whitePiece.signalExit(Pieces.White_rook)
                }
            }

            Image {
                width: whitePiece.width/2
                height: whitePiece.height/2
                source: Pieces.White_knight
                MouseArea {
                    anchors.fill: parent
                    onClicked: whitePiece.signalExit(Pieces.White_knight)
                }
            }

            Image {
                width: whitePiece.width/2
                height: whitePiece.height/2
                source: Pieces.White_bishop
                MouseArea {
                    anchors.fill: parent
                    onClicked: whitePiece.signalExit(Pieces.White_bishop)
                }
            }
        }
    }
}
