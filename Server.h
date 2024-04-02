#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>

#include <iostream>
using namespace std;




class Server
{
public:
    Server();

private:
    void Listening();
    void CreateSocket();

    int sock;
    bool running;
    sockaddr_in addr;


};


#endif