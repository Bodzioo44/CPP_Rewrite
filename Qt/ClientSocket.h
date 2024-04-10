#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H


#include <QTcpSocket>
#include <QMainWindow>
#include <QJsonDocument>

#include <QJsonObject>
#include <QJsonArray>
#include <QObject>

class ClientSocket
{
    public:
        ClientSocket(QMainWindow* parent);
        bool Connect();
        bool SendData(QByteArray data);
        QJsonDocument Received();

    private:
        QTcpSocket* socket;
};


#endif 