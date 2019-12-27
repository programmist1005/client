#include "game.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------
namespace {
int s_playerNumber = -1;
bool s_wait = false;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
Game::Game(QObject *parent) : MovePiece(parent)
{

}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::requestWaitPlayerMove(const bool wait)
{
    s_wait = wait;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::checkPiecePosition(const int dragPos,const int targetPos)
{
    int dragPosHor = -1, dragPosVert = -1, targetPosHor = -1, targetPosVert = -1;

    for (int hor = 0; hor<8; ++hor){
        for (int vert = 0; vert<8; ++vert){
            if (dragPos == (8*hor+vert)){
                dragPosHor = hor;
                dragPosVert = vert;
            }else if (targetPos == (8*hor+vert)){
                targetPosHor = hor;
                targetPosVert = vert;
            }
        }
    }
    if (dragPos == targetPos){
        emit dropPiece(dragPos, gameBoard[dragPosHor][dragPosVert], dragPos);
        return;
    }else{
        checkMovePiece(dragPos,dragPosHor,dragPosVert,targetPos,targetPosHor,targetPosVert);
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool Game::checkPlayerAndPiece(const QString dragPiece)
{
    bool check = false;
    if ((getPlayerNumber() == 1 && waitPlayerMove() == false &&
        (dragPiece == White_pawn   || dragPiece == White_rook  || dragPiece == White_knight ||
         dragPiece == White_bishop || dragPiece == White_queen || dragPiece == White_king)) ||

        (getPlayerNumber() == 2 && waitPlayerMove() == false &&
        (dragPiece == Black_pawn   || dragPiece == Black_rook  || dragPiece == Black_knight ||
         dragPiece == Black_bishop || dragPiece == Black_queen || dragPiece == Black_king))){
        check = true;
    }
    return check;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::selectNewPiece(const QString newPiece)
{
    for (int vert = 0; vert < 8; ++vert){
        if (gameBoard[0][vert] == White_pawn){
            gameBoard[0][vert] = newPiece;
        }else if (gameBoard[7][vert] == Black_pawn){
            gameBoard[7][vert] = newPiece;
            saveGameBoard(newPiece, getPlayerNumber());
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool Game::waitPlayerMove() const
{
    return s_wait;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::setPlayerNumber(const int playerNumber)
{
    s_playerNumber = playerNumber;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
int Game::getPlayerNumber() const
{
    return s_playerNumber;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::checkMovePiece(const int dragPos,const int dragPosHor,const int dragPosVert,const int targetPos,const int targetPosHor,const int targetPosVert)
{
    static bool moveWhitePiece = true;
    static bool moveBlackPiece = false;

    static QString lastMovePiece = None_piece;      // for capture pawn
    static int lastMoveTargetPosHor = -1;
    static int lastMoveTargetPosVert = -1;

    static bool castlingShortBlackPiece = true;
    static bool castlingLongBlackPiece = true;
    static bool castlingShortWhitePiece = true;
    static bool castlingLongWhitePiece = true;

    QString dragPiece = gameBoard[dragPosHor][dragPosVert];
    QString targetPiece = gameBoard[targetPosHor][targetPosVert];

    int dropPos = dragPos;
    int typeTargetCell = targetCell(targetPiece);
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_pawn && moveWhitePiece == true && typeTargetCell == 0)  ||
         (dragPiece == Black_pawn && moveBlackPiece == true && typeTargetCell == 0)) &&
         movePawn(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
        replacePawn(targetPosHor);
    }else if (((dragPiece == White_pawn && moveWhitePiece == true && typeTargetCell == 2)  ||
               (dragPiece == Black_pawn && moveBlackPiece == true && typeTargetCell == 1)) &&
               movePawnAttack(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
               checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
        replacePawn(targetPosHor);
    }else if (((dragPiece == White_pawn && moveWhitePiece == true && typeTargetCell == 0)  ||
               (dragPiece == Black_pawn && moveBlackPiece == true && typeTargetCell == 0)) &&
               movePawnCapture(dragPosHor, targetPosHor, targetPosVert, lastMoveTargetPosVert) == true){
        gameBoard[lastMoveTargetPosHor][lastMoveTargetPosVert] = None_piece;
        if (checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) != true){
            gameBoard[lastMoveTargetPosHor][lastMoveTargetPosVert] = lastMovePiece;
        }else{
            emit capturePawn(8*lastMoveTargetPosHor+lastMoveTargetPosVert);
            dropPos = targetPos;
        }
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_rook && moveWhitePiece == true && (typeTargetCell == 0 || typeTargetCell == 2))  ||
         (dragPiece == Black_rook && moveBlackPiece == true && (typeTargetCell == 0 || typeTargetCell == 1))) &&
         moveRook(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_knight && moveWhitePiece == true && (typeTargetCell == 0 || typeTargetCell == 2))  ||
         (dragPiece == Black_knight && moveBlackPiece == true && (typeTargetCell == 0 || typeTargetCell == 1))) &&
         moveKnight(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_bishop && moveWhitePiece == true && (typeTargetCell == 0 || typeTargetCell == 2))  ||
         (dragPiece == Black_bishop && moveBlackPiece == true && (typeTargetCell == 0 || typeTargetCell == 1))) &&
         moveBishop(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_queen && moveWhitePiece == true && (typeTargetCell == 0 || typeTargetCell == 2))  ||
         (dragPiece == Black_queen && moveBlackPiece == true && (typeTargetCell == 0 || typeTargetCell == 1))) &&
         (moveRook(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true   ||
         moveBishop(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true) &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_king && moveWhitePiece == true && (typeTargetCell == 0 || typeTargetCell == 2))  ||
         (dragPiece == Black_king && moveBlackPiece == true && (typeTargetCell == 0 || typeTargetCell == 1))) &&
         moveKing(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
    }
    //------------------------------------------------------------------------------------------------------------
    if (((dragPiece == White_king && moveWhitePiece == true && castlingShortWhitePiece == true)  ||
         (dragPiece == Black_king && moveBlackPiece == true && castlingShortBlackPiece == true)) &&
         castlingShort(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
         checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
        gameBoard[dragPosHor][dragPosVert+1] = gameBoard[dragPosHor][dragPosVert+3];
        gameBoard[dragPosHor][dragPosVert+3] = None_piece;
        emit castling(targetPos+1, targetPos-1, gameBoard[dragPosHor][dragPosVert+1]);
    }else if (((dragPiece == White_king && moveWhitePiece == true && castlingLongWhitePiece == true) ||
               (dragPiece == Black_king && moveBlackPiece == true && castlingLongBlackPiece == true)) &&
               castlingLong(dragPosHor, dragPosVert, targetPosHor, targetPosVert) == true &&
               checkmate(dragPosHor, dragPosVert,  targetPosHor, targetPosVert) == true){
        dropPos = targetPos;
        gameBoard[dragPosHor][dragPosVert-1] = gameBoard[dragPosHor][dragPosVert-4];
        gameBoard[dragPosHor][dragPosVert-4] = None_piece;
        emit castling(targetPos-2, targetPos+1, gameBoard[dragPosHor][dragPosVert-1]);
    }
    //------------------------------------------------------------------------------------------------------------
    if (dropPos != dragPos){
        if (moveWhitePiece){
            moveWhitePiece = false;
            moveBlackPiece = true;
        }else{
            moveWhitePiece = true;
            moveBlackPiece = false;
        }
        if (dragPiece == Black_king){
            castlingShortBlackPiece = false;
            castlingLongBlackPiece = false;
        }else if (dragPiece == White_king){
            castlingShortWhitePiece = false;
            castlingLongWhitePiece = false;
        }
        switch (dragPos){
        case 0: castlingLongBlackPiece = false;
            break;
        case 7: castlingShortBlackPiece = false;
            break;
        case 56: castlingLongWhitePiece = false;
            break;
        case 63: castlingShortWhitePiece = false;
            break;
        }
        if ((dragPiece == Black_pawn && dragPosHor == 1 && targetPosHor == 3) ||
            (dragPiece == White_pawn && dragPosHor == 6 && targetPosHor == 4)){
            lastMovePiece = dragPiece;
            lastMoveTargetPosHor = targetPosHor;
            lastMoveTargetPosVert = targetPosVert;
        }else{
            lastMovePiece = None_piece;
        }
        emit dropPiece(dragPos, dragPiece, dropPos);
        saveGameBoard(dragPiece, getPlayerNumber());
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
bool Game::checkmate(const int dragPosHor,const int dragPosVert,const int targetPosHor,const int targetPosVert)
{
    bool update = false;
    QString dragPiece = gameBoard[dragPosHor][dragPosVert];
    QString targetPiece = gameBoard[targetPosHor][targetPosVert];

    gameBoard[targetPosHor][targetPosVert] = dragPiece;
    gameBoard[dragPosHor][dragPosVert] = None_piece;

    if ((dragPiece == White_pawn || dragPiece == White_rook  || dragPiece == White_knight  ||
         dragPiece == White_king || dragPiece == White_queen || dragPiece == White_bishop) &&
         checkKing(White_king) != true){
        update = true;
    }else if ((dragPiece == Black_pawn || dragPiece == Black_rook  || dragPiece == Black_knight  ||
               dragPiece == Black_king || dragPiece == Black_queen || dragPiece == Black_bishop) &&
               checkKing(Black_king) != true){
        update = true;
    }else{
        gameBoard[targetPosHor][targetPosVert] = targetPiece;
        gameBoard[dragPosHor][dragPosVert] = dragPiece;
    }
    return update;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void Game::replacePawn(const int targetPosHor)
{
    switch (targetPosHor){
    case 0: emit replaceWhitePawn(getPlayerNumber());
        break;
    case 7: emit replaceBlackPawn(getPlayerNumber());
        break;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
int Game::targetCell(const QString targetPiece)
{
    int typeTargetCell = -1; // "0" - None piece, "1" - White piece, "2" - Black piece

    if (targetPiece == None_piece){
        typeTargetCell = 0;
    }else if (targetPiece == White_pawn || targetPiece == White_rook  || targetPiece == White_knight ||
              targetPiece == White_king || targetPiece == White_queen || targetPiece == White_bishop){
        typeTargetCell = 1;
    }else if (targetPiece == Black_pawn || targetPiece == Black_rook  || targetPiece == Black_knight ||
              targetPiece == Black_king || targetPiece == Black_queen || targetPiece == Black_bishop){
        typeTargetCell = 2;
    }
    return typeTargetCell;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
