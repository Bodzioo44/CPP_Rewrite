#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>


#include <vector>
#include <map>
#include <algorithm>

#include <iostream>
using namespace std;

const int PORT = 4444;
timeval timeout = {5, 0};


class Server
{
public:
    Server();

private:
    void Listening();
    void CreateSocket();
    void HandleMessage(int clientSocket);
    void Send(int clients, string message);
    void AssignClient();
    void DisconnectClient(int clientSocket);

    int serverSocket; //server socket
    bool running;
    sockaddr_in serverAddress; //server addr
    vector<int> clients; //fds 
    map<string, int> clientsMap; //client name/fd map?


};


#endif