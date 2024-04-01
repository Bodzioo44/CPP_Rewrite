#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
public:
    Server();

private:
    int sock;

};



#endif