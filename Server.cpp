#include "Server.h"


Server::Server()
{
    clients = {};
    running = true;

    CreateSocket();
    Listening();
}

void Server::HandleMessage(int clientSocket)
{
    char buffer[1024] = { 0 };
    ssize_t numbytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (numbytes == 0) {DisconnectClient(clientSocket);}
    else 
    {
        json message = json::parse(buffer);
        cout << message.dump(4) << endl;
        for (json::iterator it = message.begin(); it != message.end(); ++it)
        {
            //cout << it.key() << " : " << it.value() << endl;
            //TODO Create string/funcion map?
            //Or just do else if?
            cout << "API: " << it.key() << " : " << it.value() << endl;
            string current_api = it.key();
            if (current_api == JOIN_LOBBY)
            {
                cout << "Joining lobby" << endl;
            }
            else if (current_api == CREATE_LOBBY)
            {
                cout << "Creating lobby" << endl;
            }
            else if (current_api == LEAVE_LOBBY)
            {
                cout << "Leaving lobby" << endl;
            }
            else if (current_api == REQUEST_LOBBY_LIST)
            {
                cout << "Requesting lobby list" << endl;
            }
            else if (current_api == UPDATE_LOBBY_LIST)
            {
                cout << "Updating lobby list" << endl;
            }
            else
            {
                cout << "Unknown API" << endl;
            }
            
        }
    }
}


void Server::CreateSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(PORT); 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, nullptr, 0);
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
            cout << "Timeouaaa!" << endl;
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

void Server::DisconnectClient(int clientSocket)
{
    close(clientSocket);
    cout << "Client with fd: " << clientSocket << " disconnected" << endl;
    clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
}


void Server::Send(int client, json message)
{
    string serialized_message = message.dump();
    cout << "Sending serialized message: " << serialized_message << endl;
    send(client, serialized_message.c_str(), serialized_message.size(), 0);

}

int main()
{
    Server server;
    return 0;
}