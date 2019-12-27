#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "mainclient.h"
#include "game.h"
#include "../server/server.h"
#include "movepiece.h"
#include "chessboard.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<MainClient>("mainClient", 1, 0, "MainClient");
    qmlRegisterType<MovePiece>("movepiece", 1, 0, "MovePiece");
    qmlRegisterType<Game>("game", 1, 0, "Game");
    qmlRegisterType<Server>("server", 1, 0, "Server");
    qmlRegisterType<ChessBoard>("chessBoard", 1, 0, "ChessBoard");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
