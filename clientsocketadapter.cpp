#include "clientsocketadapter.h"
#include "mainclient.h"

ClientSocketAdapter::ClientSocketAdapter(QObject *parent) : SocketAdapter(parent)
{
    tcpSocket->connectToHost("localhost", mainClient->getPortNumber());
}
