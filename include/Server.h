#ifndef SERVER_H
#define SERVER_H

#include "Socket.h"
#include <string>
#include <vector>

namespace WEBSERVER{

class BaseServer : public BaseSocket{
private:
    SOCKET listenSocket;
    int port;
    SOCKET clientSocket;
    std::string IPAddress;
    sockaddr_in serverAddr;
    std::string IPtype;

public:
    BaseServer();
    ~BaseServer();
};


class Server {
private:
    enum ErrorID {
        Error_InitWSA, Error_CreatSocket, Error_InvalidAddr, Error_BindSocket, 
        Error_ListenSocket, Error_AcceptSocket, Error_ReceiveData, Error_SendData
    };
    WSADATA wsaData;
    SOCKET listenSocket;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    int port;
    char ip[4];
    std::string ipAddress;

    void Error(ErrorID id);
public:
    Server();
    ~Server();
    void start();
};

};

#endif