#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QDebug>

#include "movepiece.h"

class Game : public MovePiece
{
    Q_OBJECT
public:
    //------------------------------------------------------------------------------------------------------------
    explicit Game(QObject *parent = nullptr);
    //------------------------------------------------------------------------------------------------------------
    Q_INVOKABLE void requestWaitPlayerMove(const bool wait); // use in Server::onNewConnection()
    //------------------------------------------------------------------------------------------------------------
protected:
    Q_INVOKABLE void checkPiecePosition(const int dragPos,const int targetPos);
    Q_INVOKABLE bool checkPlayerAndPiece(const QString dragPiece);
    Q_INVOKABLE void selectNewPiece(const QString newPiece);
    Q_INVOKABLE bool waitPlayerMove() const;
    Q_INVOKABLE void setPlayerNumber(const int playerNumber);
    Q_INVOKABLE int getPlayerNumber() const;
    //------------------------------------------------------------------------------------------------------------
private:
    //------------------------------------------------------------------------------------------------------------
    void checkMovePiece(const int dragPos,const int dragPosHor,const int dragPosVert,const int targetPos,const int targetPosHor,const int targetPosVert);
    bool checkmate(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert);
    void replacePawn(const int targetPosHor);
    int targetCell(const QString targetPiece);
    //------------------------------------------------------------------------------------------------------------
private: signals:
    //------------------------------------------------------------------------------------------------------------
    void dropPiece(int dragPos, QString dragPiece, int dropPos);
    void castling(int dragPos, int dropPos, QString rook);
    void capturePawn(int capturePawnPos);
    void replaceWhitePawn(int playerNumber);
    void replaceBlackPawn(int playerNumber);
    //------------------------------------------------------------------------------------------------------------
};

#endif // GAME_H
