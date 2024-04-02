#include "Server.h"

Server::Server()
{
    running = true;

    
    
    int clientSocket = accept(sock, nullptr, nullptr);
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Message from client: " << buffer << endl;
    close(sock);
}

void Server::CreateSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //this will listen on all interfaces
    bind(sock, (struct sockaddr*) &addr, sizeof(addr));
}


void Server::Listening()
{
    listen(sock, 1024);
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);


    while (running)
    {
        int activity = select()
    }
}






int main()
{
    Server server;
    return 0;
}