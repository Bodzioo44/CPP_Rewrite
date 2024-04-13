#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <arpa/inet.h>


#include <vector>
#include <map>
#include <algorithm>
#include "json.hpp"


#include <iostream>
using namespace std;
using json = nlohmann::json;

const int PORT = 4444;
timeval timeout = {5, 0};

const string JOIN_LOBBY = "Join_Lobby";
const string CREATE_LOBBY = "Create_Lobby";
const string LEAVE_LOBBY = "Leave_Lobby";
const string REQUEST_LOBBY_LIST = "Request_Lobby_List";
const string UPDATE_LOBBY_LIST = "Update_Lobby";


class Server
{
public:
    Server();

private:
    void Listening();
    void CreateSocket();
    void HandleMessage(int clientSocket);
    void Send(int client, json message);
    void AssignClient();
    void DisconnectClient(int clientSocket);

    int serverSocket; //server socket
    bool running;
    sockaddr_in serverAddress; //server addr
    vector<int> clients; //fds 
    map<string, int> clientsMap; //client name/fd map?


};


#endif