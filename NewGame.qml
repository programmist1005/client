import QtQml.Models 2.3
import QtQuick 2.6
import game 1.0
import mainClient 1.0
import chessBoard 1.0
import "pieces.js" as Pieces

Rectangle {
    id: fon
    width: parent.width
    height: parent.height
    color: "BurlyWood"

    Board {
        id: board
    }

    ChessBoard {
        id: chessBoard
    }

    GridView {
        id: gridView
        interactive: false
        cellHeight: height/8
        cellWidth: width/8
        anchors. top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: parent.width/18
        anchors.topMargin: parent.height/18
        anchors.rightMargin: parent.width/18
        anchors.bottomMargin: parent.height/18

        MainClient {
            id: mainClient
            onServerMessage:{
                if( game.waitPlayerMove() === true ){
                    game.selectNewPiece(dragPiece)
                    game.requestWaitPlayerMove(false)
                }
                game.checkPiecePosition(dragPos, targetPos)
            }
        }

        Game {
            id: game
            onDropPiece:{
                sourseListModel.setProperty(dragPos, "sourse", Pieces.None_piece)
                sourseListModel.setProperty(dropPos, "sourse", dragPiece)
            }
            onCapturePawn:{
                sourseListModel.setProperty(capturePawnPos, "sourse", Pieces.None_piece)
            }
            onCastling:{
                sourseListModel.setProperty(dragPos, "sourse", Pieces.None_piece)
                sourseListModel.setProperty(dropPos, "sourse", rook)
            }
            onReplaceWhitePawn:{
                if( playerNumber === 1 ){
                    whitePiece.open()
                }else{
                    game.requestWaitPlayerMove(true)
                }
            }
            onReplaceBlackPawn:{
                if( playerNumber === 2 ){
                    blackPiece.open()
                }else{
                    game.requestWaitPlayerMove(true)
                }
            }
        }

        WhitePiece {
            id: whitePiece
            onSignalExit:{
                game.selectNewPiece(newPiece)
                mainClient.send(mainClient.getTargetPos())
                mainClient.send(newPiece)
                mainClient.send(mainClient.getTargetPos())
                whitePiece.close()
            }
        }

        BlackPiece {
            id: blackPiece
            onSignalExit:{
                game.selectNewPiece(newPiece)
                mainClient.send(mainClient.getTargetPos())
                mainClient.send(newPiece)
                mainClient.send(mainClient.getTargetPos())
                blackPiece.close()
            }
        }

        model: DelegateModel {
            id: visualModel

            model: ListModel {
                id: sourseListModel

                Component.onCompleted:{
                    var hor
                    var vert

                    for (hor = 0; hor<8; ++hor){
                        for (vert = 0; vert<8; ++vert){
                            append( { sourse: chessBoard.addPieceForNewGame(hor,vert) })
                        }
                    }
                }
            }

            delegate: MouseArea {
                id: mouseArea

                property bool held: false
                property int visualIndex: DelegateModel.itemsIndex

                width: gridView.cellWidth
                height: gridView.cellHeight

                drag.target: held ? cell : undefined

                drag.maximumX: gridView.width - (board.width)/8
                drag.minimumX: -1
                drag.maximumY: gridView.height - (board.height)/8
                drag.minimumY: -1

                onPressed:{
                    var cellSourse = sourseListModel.get(mouseArea.visualIndex).sourse

                    if(cellSourse !== Pieces.None_piece){
                        held = true
                        cell.opacity = 0.5
                    }
                    if(cellSourse === Pieces.None_piece){
                        held = false
                    }
                }

                onReleased:{
                    if(held === true){
                        held = false
                        cell.opacity = 1
                        cell.Drag.drop()
                    }else{
                    }
                }

                Image {
                    id: cell
                    width: gridView.cellWidth
                    height: gridView.cellHeight
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: model.sourse

                    Drag.active: mouseArea.drag.active
                    Drag.source: mouseArea
                    Drag.hotSpot.x: gridView.cellWidth/2
                    Drag.hotSpot.y: gridView.cellHeight/2

                    Component.onCompleted:{
                        if( game.getPlayerNumber() === 2 ){
                            fon.rotation = 180
                            cell.rotation = 180
                        }
                    }

                    states:[
                        State {
                            when: cell.Drag.active

                            ParentChange {
                                target: cell
                                parent: gridView
                            }

                            AnchorChanges {
                                target: cell
                                anchors.horizontalCenter: undefined
                                anchors.verticalCenter: undefined
                            }
                        }
                    ]
                }

                DropArea {
                    id: dropArea
                    anchors.fill: parent
                    width: gridView.cellWidth
                    height: gridView.cellHeight

                    onDropped:{
                        var dragPos = drag.source.visualIndex
                        var dragPiece = sourseListModel.get(drag.source.visualIndex).sourse

                        var targetPos = mouseArea.visualIndex

                        if( game.checkPlayerAndPiece(dragPiece) === true ){
                            mainClient.send(dragPos)
                            mainClient.send(dragPiece)
                            mainClient.send(targetPos)
                        }
                    }
                }
            }
        }
    }
}
