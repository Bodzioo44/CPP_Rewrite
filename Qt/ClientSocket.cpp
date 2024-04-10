#include "ClientSocket.h"


ClientSocket::ClientSocket(QMainWindow* parent)
{
    socket = new QTcpSocket(parent);
}


bool ClientSocket::Connect()
{
    socket->connectToHost("127.0.0.1", 4444);
    if (socket->waitForConnected(5000)) {return true;}
    else {return false;}
}

bool ClientSocket::SendData(QByteArray data)
{
    if (socket->write(data) == -1) {return false;}
    else {return true;}
}

QJsonDocument ClientSocket::Received()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc;
}