#ifndef CLIENTSOCKETADAPTER_H
#define CLIENTSOCKETADAPTER_H

#include <QVector>
#include <QTcpSocket>
#include <QDataStream>

#include "../common/socketadapter.h"

class MainClient;

class ClientSocketAdapter : public SocketAdapter
{
    Q_OBJECT
public:
    explicit ClientSocketAdapter(QObject *parent);
protected:
    MainClient *mainClient;
};

#endif // CLIENTSOCKETADAPTER_H
