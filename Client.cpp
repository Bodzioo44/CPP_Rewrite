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

ssize_t bytesSent = send(clientSocket, message, strlen(message), 0); 
if (bytesSent == -1) {
    std::cout << "\nSend failed \n";
    return;
} else {
    std::cout << "Sent " << bytesSent << " bytes\n";
}
    cout << "sent";
    sleep(5);
    // closing socket 
    close(clientSocket); 
}
