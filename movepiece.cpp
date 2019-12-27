#include "movepiece.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------
MovePiece::MovePiece(QObject *parent) : ChessBoard(parent)
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::movePawn(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool move = false;

    if ((gameBoard[dragPosHor][dragPosVert] == White_pawn &&
       ((targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert) ||
        (targetPosHor == dragPosHor-2 && targetPosVert == dragPosVert && dragPosHor == 6 && gameBoard[dragPosHor-1][dragPosVert] == None_piece))) ||

        (gameBoard[dragPosHor][dragPosVert] == Black_pawn  &&
       ((targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert) ||
        (targetPosHor == dragPosHor+2 && targetPosVert == dragPosVert && dragPosHor == 1 && gameBoard[dragPosHor+1][dragPosVert] == None_piece)))){
        move = true;
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::movePawnAttack(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool move = false;

    if (gameBoard[dragPosHor][dragPosVert] == White_pawn &&
       (targetPosHor == dragPosHor-1 && (targetPosVert == dragPosVert-1 || targetPosVert == dragPosVert+1))){
        move = true;
    }else if (gameBoard[dragPosHor][dragPosVert] == Black_pawn &&
             (targetPosHor == dragPosHor+1 && (targetPosVert == dragPosVert-1 || targetPosVert == dragPosVert+1))){
        move = true;
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::movePawnCapture(const int dragPosHor,const int targetPosHor,const int targetPosVert,const int lastMoveTargetPosVert)
{
    bool move = false;

    if (targetPosVert == lastMoveTargetPosVert &&
       ((gameBoard[dragPosHor][lastMoveTargetPosVert] == White_pawn && targetPosHor == dragPosHor+1 && dragPosHor == 4) ||
        (gameBoard[dragPosHor][lastMoveTargetPosVert] == Black_pawn && targetPosHor == dragPosHor-1 && dragPosHor == 3))){
        move = true;
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::moveRook(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    int right = 0, left = 0, down = 0, up = 0;
    bool move = false;

    for (int i = 1; i < 8; ++i){
        if (targetPosHor == dragPosHor && targetPosVert == dragPosVert+i){
            for (int j = dragPosVert+1; j < targetPosVert; ++j){
                if (gameBoard[dragPosHor][j] == None_piece){
                    ++right;
                }
            }if (right == (targetPosVert-dragPosVert-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor && targetPosVert == dragPosVert-i){
            for (int j = targetPosVert+1; j < dragPosVert; ++j){
                if (gameBoard[dragPosHor][j] == None_piece){
                    ++left;
                }
            }if (left == (dragPosVert-targetPosVert-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor+i && targetPosVert == dragPosVert){
            for (int j = dragPosHor+1; j < targetPosHor; ++j){
                if (gameBoard[j][dragPosVert] == None_piece){
                    ++down;
                }
            }if (down == (targetPosHor-dragPosHor-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor-i && targetPosVert == dragPosVert){
            for (int j = targetPosHor+1; j < dragPosHor; ++j){
                if (gameBoard[j][dragPosVert] == None_piece){
                    ++up;
                }
            }if (up == (dragPosHor-targetPosHor-1)){
                move = true;
            }
        }
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::moveKnight(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool move = false;

    if ((targetPosHor == dragPosHor-2 && targetPosVert == dragPosVert-1) ||
        (targetPosHor == dragPosHor-2 && targetPosVert == dragPosVert+1) ||
        (targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert-2) ||
        (targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert+2) ||
        (targetPosHor == dragPosHor+2 && targetPosVert == dragPosVert-1) ||
        (targetPosHor == dragPosHor+2 && targetPosVert == dragPosVert+1) ||
        (targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert-2) ||
        (targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert+2)){
        move = true;
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::moveBishop(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    int up_right = 0, up_left = 0, down_right = 0, down_left = 0;
    bool move = false;

    for (int i = 1; i < 8; ++i){
        if (targetPosHor == dragPosHor-i && targetPosVert == dragPosVert+i){
            for (int j = 1; j < (dragPosHor-targetPosHor); ++j){
                if (gameBoard[dragPosHor-j][dragPosVert+j] == None_piece){
                    ++up_right;
                }
            }if (up_right == (dragPosHor-targetPosHor-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor-i && targetPosVert == dragPosVert-i){
            for (int j = 1; j < (dragPosHor-targetPosHor); ++j){
                if (gameBoard[dragPosHor-j][dragPosVert-j] == None_piece){
                    ++up_left;
                }
            }if (up_left == (dragPosHor-targetPosHor-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor+i && targetPosVert == dragPosVert+i){
            for (int j = 1; j < (targetPosHor-dragPosHor); ++j){
                if (gameBoard[dragPosHor+j][dragPosVert+j] == None_piece){
                    ++down_right;
                }
            }if (down_right == (targetPosHor-dragPosHor-1)){
                move = true;
            }
        }else if (targetPosHor == dragPosHor+i && targetPosVert == dragPosVert-i){
            for (int j = 1; j < (targetPosHor-dragPosHor); ++j){
                if (gameBoard[dragPosHor+j][dragPosVert-j] == None_piece){
                    ++down_left;
                }
            }if (down_left == (targetPosHor-dragPosHor-1)){
                move = true;
            }
        }
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::moveKing(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool move = false;

    if ((targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert)   ||
        (targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert)   ||
        (targetPosHor == dragPosHor   && targetPosVert == dragPosVert-1) ||
        (targetPosHor == dragPosHor   && targetPosVert == dragPosVert+1) ||
        (targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert-1) ||
        (targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert+1) ||
        (targetPosHor == dragPosHor-1 && targetPosVert == dragPosVert+1) ||
        (targetPosHor == dragPosHor+1 && targetPosVert == dragPosVert-1)){
        move = true;
    }
    return move;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::castlingShort(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool castling = false;

    if (targetPosHor == dragPosHor && targetPosVert == dragPosVert+2 &&
        gameBoard[dragPosHor][dragPosVert+1] == None_piece  &&
        gameBoard[dragPosHor][dragPosVert+2] == None_piece  &&
      ((gameBoard[dragPosHor][dragPosVert+3] == White_rook)  ||
       (gameBoard[dragPosHor][dragPosVert+3] == Black_rook))){
        castling = true;
    }
    return castling;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::castlingLong(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool castling = false;

    if (targetPosHor == dragPosHor && targetPosVert == dragPosVert-2 &&
        gameBoard[dragPosHor][dragPosVert-1] == None_piece  &&
        gameBoard[dragPosHor][dragPosVert-2] == None_piece  &&
        gameBoard[dragPosHor][dragPosVert-3] == None_piece  &&
      ((gameBoard[dragPosHor][dragPosVert-4] == White_rook)  ||
       (gameBoard[dragPosHor][dragPosVert-4] == Black_rook))){
        castling = true;
    }
    return castling;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool MovePiece::checkKing(const QString king)
{
    bool check = false;
    int kingPosHor = -1;
    int kingPosVert = -1;

    for (int hor = 0; hor<8; ++hor){
        for (int vert = 0; vert<8; ++vert){
            if (gameBoard[hor][vert] == king){
                kingPosHor = hor;
                kingPosVert = vert;
            }
        }
    }
    for (int i = 0; i<8; ++i){
        for (int j = 0; j<8; ++j){

            if  (king == White_king &&
               ((gameBoard[i][j] == Black_rook &&
                 moveRook(i, j, kingPosHor, kingPosVert) == true)    ||
                (gameBoard[i][j] == Black_knight &&
                 moveKnight(i, j, kingPosHor, kingPosVert) == true)  ||
                (gameBoard[i][j] == Black_bishop &&
                 moveBishop(i, j, kingPosHor, kingPosVert) == true)  ||
                (gameBoard[i][j] == Black_queen &&
                (moveRook(i, j, kingPosHor, kingPosVert) == true     ||
                 moveBishop(i, j, kingPosHor, kingPosVert) == true)) ||
                (gameBoard[i][j] == Black_king &&
                 moveKing(i, j, kingPosHor, kingPosVert) == true)   ||
                (gameBoard[i][j] == Black_pawn &&
                 movePawnAttack(i, j, kingPosHor, kingPosVert) == true))){

                check = true;
        }
            if  (king == Black_king &&
               ((gameBoard[i][j] == White_rook &&
                 moveRook(i, j, kingPosHor, kingPosVert) == true)    ||
                (gameBoard[i][j] == White_knight &&
                 moveKnight(i, j, kingPosHor, kingPosVert) == true)  ||
                (gameBoard[i][j] == White_bishop &&
                 moveBishop(i, j, kingPosHor, kingPosVert) == true)  ||
                (gameBoard[i][j] == White_queen &&
                (moveRook(i, j, kingPosHor, kingPosVert) == true     ||
                 moveBishop(i, j, kingPosHor, kingPosVert) == true)) ||
                (gameBoard[i][j] == White_king &&
                 moveKing(i, j, kingPosHor, kingPosVert) == true)   ||
                (gameBoard[i][j] == White_pawn &&
                 movePawnAttack(i, j, kingPosHor, kingPosVert) == true))){

                check = true;
            }
        }
    }
    return check;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
