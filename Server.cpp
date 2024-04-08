#include "Server.h"


Server::Server()
{
    clients = {};
    running = true;

    CreateSocket();
    Listening();
}

void Server::CreateSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(PORT); 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
}

void Server::Listening()
{
    listen(serverSocket, SOMAXCONN); 
    while (running)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);
        FD_SET(STDIN_FILENO, &readfds);
        int max_sock_value = serverSocket;
        if (STDIN_FILENO > max_sock_value)
        {
            max_sock_value = STDIN_FILENO;
        }
        for (int clientSocket : clients)
        {
            FD_SET(clientSocket, &readfds);
            if (clientSocket > max_sock_value)
            {
                max_sock_value = clientSocket;
            }
            Send(clientSocket, "Hello, client!");
        }
        timeout.tv_sec = 3;
        int activity = select(max_sock_value + 1, &readfds, nullptr, nullptr, &timeout);

        if (activity > 0)
        {
            if (FD_ISSET(serverSocket, &readfds))
            {
                AssignClient();
            }
            else if (FD_ISSET(STDIN_FILENO, &readfds))
            {
                string input;
                getline(cin, input);
                if (input == "exit")
                {
                    running = false;
                }
                cout << input << endl;
            }
            else
            {
                for (int clientSocket : clients)
                {
                    if (FD_ISSET(clientSocket, &readfds))
                    {    
                        HandleMessage(clientSocket);
                    }
                }
            }
        }

        else if (activity < 0)
        {
            cout << "Select error, something went wrong!" << endl;
            perror("select");
        }
        else
        {
            cout << "Timeout!" << endl;
        }
    }
    close(serverSocket); 
}

void Server::AssignClient()
{
    // TODO add error handling, store client addresses?
    // sockaddr_in clientAddress;
    // socklen_t clientSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    cout << "Client connected with fd: " << clientSocket << endl;
    clients.push_back(clientSocket);
}

void Server::HandleMessage(int clientSocket)
{
    char buffer[1024] = { 0 };
    ssize_t numbytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (numbytes == 0) {DisconnectClient(clientSocket);}
    else {std::cout << "Message from client: " << buffer << endl;}
}

void Server::DisconnectClient(int clientSocket)
{
    close(clientSocket);
    cout << "Client with fd: " << clientSocket << " disconnected" << endl;
    clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
}


void Server::Send(int client, string message)
{
    cout << "Sending message to client: " << client << endl;
    send(client, message.c_str(), message.size(), 0);

}

int main()
{
    Server server;
    return 0;
}