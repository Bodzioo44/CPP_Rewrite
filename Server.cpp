#include "Server.h"

#include <iostream>


Server::Server()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    //std::cout << sock << std::endl;
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(4444);
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //this will listen on all interfaces
    bind(sock, (struct sockaddr*) &addr, sizeof(addr));
}





int main()
{
    Server server;
    return 0;
}