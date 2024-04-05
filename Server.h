#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>


#include <vector>
#include <iostream>
using namespace std;

const int PORT = 4444;
timeval timeout = {3, 0};


class Server
{
public:
    Server();

private:
    void Listening();
    void CreateSocket();
    void HandleMessage(int clientSocket);
    void AssignClient();

    int sock; //server socket
    bool running;
    sockaddr_in addr; //server addr
    vector<int> clients;


};


#endif