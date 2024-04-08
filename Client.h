#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#include <QThread>
#include <QObject>

#include <iostream>
using namespace std;

class Client
{
public:
    Client();

private:

};


class ListeningThread : public QThread
{
    Q_OBJECT

    public:
        ListeningThread();
        void run(int serverSocket);
    private:
        bool runnnig;
        timeval timeout = {3, 0};
};


#endif