import QtQuick 2.6

Item {
    id: board
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: parent.width/18
    anchors.topMargin: parent.height/18
    anchors.rightMargin: parent.width/18
    anchors.bottomMargin: parent.height/18

    Row {
        x: 0
        y: -board.height/16

        Repeater {
            model:[ "A", "B", "C", "D", "E", "F", "G", "H" ]

            delegate: Text {
                width: board.width/8
                height: board.height/16
                text: modelData
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: board.height/16
            }
        }
    }

    Row {
        x: 0
        y: board.height

        Repeater {
            model:[ "A", "B", "C", "D", "E", "F", "G", "H" ]

            delegate: Text {
                width: board.width/8
                height: board.height/16
                text: modelData
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: board.height/16
            }
        }
    }

    Column {
        x: -board.width/16
        y: 0

        Repeater {
            model: 8

            delegate: Text {
                width: board.width/16
                height: board.height/8
                text: 8 - index
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: board.height/16
            }
        }
    }

    Column {
        x: board.width
        y: 0

        Repeater {
            model: 8

            delegate: Text {
                width: board.width/16
                height: board.height/8
                text: 8 - index
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: board.height/16
            }
        }
    }

    Row {

        Repeater {
            model: 4

            Column {

                Repeater {
                    model: 4

                    Grid {
                        rows: 2
                        columns: 2

                        Rectangle { color: "white"; width: board.width/8; height: board.height/8 }
                        Rectangle { color: "gray"; width: board.width/8; height: board.height/8 }
                        Rectangle { color: "gray"; width: board.width/8; height: board.height/8 }
                        Rectangle { color: "white"; width: board.width/8; height: board.height/8 }
                    }
                }
            }
        }
    }
}
