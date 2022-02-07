#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <exception>

using namespace std;

class ClientException: public exception {
public:
    virtual const char* what() const throw(){
        return "Size exceeded!";
    }
};

int main()
{
    ClientException clientException;

// CLIENT

    cout << "============THE CLIENT===========" << endl;

    sockaddr_in clientSocket;
    sockaddr_in clientService;

    string address = "127.0.0.1";   // The IP address

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];


// CREATING the client socket below
    cout << "The CLIENT Socket being created" << endl;

    int clientSock = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSock == -1)
        cout << "There has been an error with creating the client socket" << endl;
    else
        cout << "Client Socket has been created!!" << endl;


// ASSIGNING the port the socket.

    clientService.sin_family = AF_INET;
    clientService.sin_port = htons(5400);
    inet_pton(AF_INET, address.c_str(), &clientService.sin_addr);


// CONNECTING to the Server socket
    cout << "Connection between the Client and Server will be set-up now!" << endl;

    int connectRes = connect(clientSock, (sockaddr*)&clientService, sizeof(clientService));
    if (connectRes == -1)
        cout << "There has been an error with connecting to the server" << endl;
    else
        cout << "The connection has been successful - we are now connected to  the Server!!" << endl;



// RECEIVING AND SENDING data back and forth between the client and server socket
    cout << "Care to have a conversation with the SERVER?" << endl;

    char sendServerMessage[500];
    while(1) {
        // Send messages from client socket
        try{
            printf("Please enter your message to send to the Server: ");
            cin.getline(sendServerMessage,500);
            int byteClientCount = send(clientSock, sendServerMessage, 500, 0);
            if (byteClientCount < 0)
                cout << "There has been an error with the send function" << endl;
            else
                cout << "The message has been sent to the client successfully!" << sendServerMessage << endl;
            if (strcmp(sendServerMessage, "QUIT")== 0) {

            }
            else if (strlen(sendServerMessage) < 500) {
                throw clientException;
            }
        }
        catch(ClientException e) {
            cout << "Exception: " << e.what() << endl;
            break;
        }


       // Receive messages from server socket

        char receiveServerMessage[500];
        int byteCount = recv(clientSock, receiveServerMessage, 500, 0);
        if (byteCount < 0)
            cout << "No message has been received from the server :(" << endl;
        else
            cout << "Server has sent you a message back:" << receiveServerMessage << endl;
            if (strcmp(receiveServerMessage, "QUIT")== 0) {
                cout << "Client Socket is Closed" << endl;
                close(clientSock);
                break;
            }
    }

    return 0;

}
