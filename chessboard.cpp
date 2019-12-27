#include "chessboard.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------
QString gameBoard[8][8];
//--------------------------------------------------------------------------------------------------------------------------------------------------
ChessBoard::ChessBoard(QObject *parent) : QObject(parent)
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------
QString ChessBoard::addPieceForNewGame(const int hor,const int vert)
{
    QFile newGame("../client/json/newGame.json");

    if (!newGame.open(QIODevice::ReadOnly)){
        qDebug()<<"ERROR";
    }
    QByteArray loadChessBoard = newGame.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(loadChessBoard);
    QJsonObject json = loadDoc.object();

    QJsonArray chessBoard = json["chessBoard"].toArray();

    for (int i = 0; i < 8; i++){
        QJsonArray piece = chessBoard[i].toArray();

        for (int j = 0; j < 8; j++){
            gameBoard[i][j] = piece[j].toString();
        }
    }
    return gameBoard[hor][vert];
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
QString ChessBoard::addPieceForContinueGame(const int hor,const int vert)
{
    QFile continueGame("../client/json/continueGame.json");

    if (!continueGame.open(QIODevice::ReadOnly)){
        qDebug()<<"ERROR";
    }
    QByteArray loadChessBoard = continueGame.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(loadChessBoard);
    QJsonObject json = loadDoc.object();

    QJsonArray chessBoard = json["chessBoard"].toArray();

    for (int i = 0; i < 8; i++){
        QJsonArray piece = chessBoard[i].toArray();

        for (int j = 0; j < 8; j++){
            gameBoard[i][j] = piece[j].toString();
        }
    }
    return gameBoard[hor][vert];
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void ChessBoard::saveGameBoard(const QString dragPiece,const int playerNumber)
{
    if (playerNumber == 0 &&
       (dragPiece == Black_pawn   || dragPiece == Black_rook  || dragPiece == Black_knight ||
        dragPiece == Black_bishop || dragPiece == Black_queen || dragPiece == Black_king)){

        QFile continueGame("../client/json/continueGame.json");
        if (!continueGame.open(QIODevice::WriteOnly)){
            qDebug()<<"ERROR";
        }
        QJsonObject json;

        QJsonArray chessBoard;
        for (int i = 0; i < 8; i++){
            QJsonArray piece;

            for (int j = 0; j < 8; j++){
                piece.append(QJsonValue(gameBoard[i][j]));
            }
            chessBoard.append(piece);
        }
        json["chessBoard"] = chessBoard;

        QJsonDocument saveDoc(json);
        continueGame.write(saveDoc.toJson());
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
