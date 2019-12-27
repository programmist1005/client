#include "mainclient.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------
namespace{
quint16 s_portNumber;
int s_targetPos;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
MainClient::MainClient(QObject *parent) : QObject(parent), socketAdapter(new ClientSocketAdapter(this))
{
    connect(socketAdapter, SIGNAL(message(QString)), SLOT(onMessage(QString)));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
quint16 MainClient::getPortNumber() const
{
    return s_portNumber;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void MainClient::send(const QString msg)
{
    socketAdapter->sendString(msg);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void MainClient::setPortNumber(const quint16 portNumber)
{
    s_portNumber = portNumber;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void MainClient::setTargetPos(const int targetPos)
{
    s_targetPos = targetPos;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
int MainClient::getTargetPos() const
{
    return s_targetPos;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
void MainClient::onMessage(QString data)
{
    static int i = 0;
    static int dragPos = -1;
    static int targetPos = -1;
    static QString dragPiece = None_piece;

    i++;
    switch (i){
    case 1: dragPos = data.toInt();
        break;
    case 2: dragPiece = data;
        break;
    case 3: targetPos = data.toInt();
            setTargetPos(targetPos);
            i = 0;
            emit serverMessage(dragPos,dragPiece,targetPos);
        break;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
