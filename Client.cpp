#include "Client.h"

Client::Client()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 
    // specifying address 
    sockaddr_in serverAddress; 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_port = htons(4444);

    if(inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr)<=0)  
    {
    std::cout << "\nInvalid address/ Address not supported \n";
    return;
    }
    std::cout << "Client socket: " << clientSocket << endl;
    // sending connection request 
    ssize_t formconnect = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); 
    cout << formconnect << endl;
    perror("connect");
    // sending data 
    cout << "Client connected to server" << endl;
    cout << "Sending message to server" << endl;
    const char* message = "Hello, server!"; 

    ListeningThread tt;
    tt.run(clientSocket);
    /*
    while (true)
    {
        char buffer[1024] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0); 
        cout << "Server: " << buffer << endl;
        sleep(1);
    }
    */
    close(clientSocket); 
}

ListeningThread::ListeningThread()
{
    runnnig = true;
}

void ListeningThread::run(int serverSocket)
{
    cout << "starting listening thread" << endl;
    while (runnnig)
    {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(serverSocket, &readfds);

        timeout.tv_sec = 3;
        int activity = select(serverSocket + 1, &readfds, nullptr, nullptr, &timeout);
        if (activity > 0)
        {
            char buffer[1024] = {0};
            recv(serverSocket, buffer, sizeof(buffer), 0);
            cout << "Server: " << buffer << endl;
        }
        else if (activity < 0)
        {
            cout << "Error in select" << endl;
        }
        else {cout << "Timeout" << endl;}
    }
}
