#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#define Black_bishop QString("qrc:/res/img/black_bishop.png")
#define Black_king QString("qrc:/res/img/black_king.png")
#define Black_knight QString("qrc:/res/img/black_knight.png")
#define Black_pawn QString("qrc:/res/img/black_pawn.png")
#define Black_queen QString("qrc:/res/img/black_queen.png")
#define Black_rook QString("qrc:/res/img/black_rook.png")
#define None_piece QString("")
#define White_bishop QString("qrc:/res/img/white_bishop.png")
#define White_king QString("qrc:/res/img/white_king.png")
#define White_knight QString("qrc:/res/img/white_knight.png")
#define White_pawn QString("qrc:/res/img/white_pawn.png")
#define White_queen QString("qrc:/res/img/white_queen.png")
#define White_rook QString("qrc:/res/img/white_rook.png")

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

class ChessBoard : public QObject
{
    Q_OBJECT
protected:
    //-----------------------------------------------------------------------------
    explicit ChessBoard(QObject *parent = nullptr);
    //-----------------------------------------------------------------------------
    Q_INVOKABLE QString addPieceForNewGame(const int hor,const int vert);
    Q_INVOKABLE QString addPieceForContinueGame(const int hor,const int vert);
    //-----------------------------------------------------------------------------
    void saveGameBoard(const QString dragPiece,const int playerNumber);
    //-----------------------------------------------------------------------------
};

extern QString gameBoard[8][8];

#endif // CHESSBOARD_H
