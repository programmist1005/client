#ifndef MOVEPIECE_H
#define MOVEPIECE_H

#include <QObject>

#include"chessboard.h"

class MovePiece : public ChessBoard
{
    Q_OBJECT
protected:
    //------------------------------------------------------------------------------------------------------------------------------
    explicit MovePiece(QObject *parent = nullptr);
    //------------------------------------------------------------------------------------------------------------------------------
    bool movePawn(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool movePawnAttack(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool movePawnCapture(const int dragPosHor, const int targetPosHor, const int targetPosVert, const int lastMoveTargetPosVert);
    bool moveRook(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool moveKnight(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool moveBishop(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool moveKing(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool castlingShort(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool castlingLong(const int dragPosHor, const int dragPosVert, const int targetPosHor, const int targetPosVert);
    bool checkKing(const QString king);
    //------------------------------------------------------------------------------------------------------------------------------
};

#endif // MOVEPIECE_H
