#ifndef MAINCLIENT_H
#define MAINCLIENT_H
#define None_piece QString("")

#include <QObject>
#include <QDebug>

#include "clientsocketadapter.h"

class ISocketAdapter;
class MainClient : public QObject
{
    Q_OBJECT
public:
    //------------------------------------------------------------------------------------------------------------
    explicit MainClient(QObject *parent = nullptr);
    //------------------------------------------------------------------------------------------------------------
    Q_INVOKABLE quint16 getPortNumber() const; // use in ClientSocketAdapter
    //------------------------------------------------------------------------------------------------------------
protected:
    //------------------------------------------------------------------------------------------------------------
    Q_INVOKABLE void send(const QString msg);
    Q_INVOKABLE void setPortNumber(const quint16 portNumber);
    Q_INVOKABLE void setTargetPos(const int targetPos);
    Q_INVOKABLE int getTargetPos() const;
    //------------------------------------------------------------------------------------------------------------
protected: signals:
    void serverMessage(int dragPos, QString dragPiece, int targetPos);
public slots:
    void onMessage(QString data);
protected:
    ISocketAdapter *socketAdapter;

};

#endif // MAINCLIENT_H
