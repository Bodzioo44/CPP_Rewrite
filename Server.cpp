#include "Server.h"

Server::Server()
{
    running = true;
    CreateSocket();
    Listening();
}

void Server::CreateSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    //addr.sin_addr.s_addr = htonl(inet_addr("127.0.0.1"));
    if(inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr)<=0)  
    {
    std::cout << "\nInvalid address/ Address not supported \n";
    return;
    }
    bind(sock, (struct sockaddr*) &addr, sizeof(addr));
}


void Server::Listening()
{
    listen(sock, SOMAXCONN);
    while (running)
    {
        //fd_set has to be reset every time select is called, to reset values
        fd_set readfds;
        FD_ZERO(&readfds);
        //FD_SETSIZE(sock, &readfds)
        FD_SET(sock, &readfds); 
        //FD_SET(STDIN_FILENO, &readfds);

        int max_sock_value = sock;
        for (int clientSocket : clients)
        {
            std::cout << "Client socket: " << clientSocket << endl;
            FD_SET(clientSocket, &readfds);
            if (clientSocket > sock)
            {
                max_sock_value = clientSocket;
            }
        }
        //std::cout << "Size of fd" << sizeof(readfds) << endl;
        timeout.tv_sec = 3;

        std::cout << "readfds size: " << sizeof(readfds) << endl;
        std::cout << "clients size: " << clients.size() << endl;
        int activity = select(max_sock_value +1, &readfds, nullptr, nullptr, nullptr);
        //select will change &readfds to show which sockets are ready to read
        //activity will be the number of sockets that are ready to read
        //0 means timeout
        std::cout << "Activity: " << activity << endl;
        if (activity > 0)
        {
            if (FD_ISSET(sock, &readfds))
            {
                AssignClient();
            }
            for (int clientSocket : clients)
            {
                if (FD_ISSET(clientSocket, &readfds))
                {
                    HandleMessage(clientSocket);
                }
            }
            /*
            if (FD_ISSET(STDIN_FILENO, &readfds))
            {
                string input;
                std::getline(std::cin, input);
                if (input == "exit")
                {
                    running = false;
                }
            }
            */
        }
        else if (activity < 0)
        {
            std::cout << "Error in select" << endl;
            perror("socket error");
            running = false;
        }
        else
        {
            std::cout << "Timed out, waiting 3 sec..." << endl;
        }
    }
}


void Server::AssignClient()
{
    sockaddr_in clientAddr;
    socklen_t clientSize = sizeof(clientAddr);
    int clientSocket = accept(sock, (struct sockaddr*) &clientAddr, &clientSize);
    clients.push_back(clientSocket);
    std::cout << "Client connected" << endl;
    //HandleMessage(clientSocket);
}


void Server::HandleMessage(int clientSocket)
{
    char buffer[1024];
    ssize_t numbytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message from client: " << buffer << endl;
    close(clientSocket);
}


int main()
{
    Server server;
    return 0;
}