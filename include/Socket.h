#ifndef SOCKET_H
#define SOCKET_H

#include "winsock2.h"
#include "ws2tcpip.h"

namespace WEBSERVER{

enum ErrorID {
    NoError, Error_InitWSA, Error_CreatSocket, Error_InvalidAddr, Error_BindSocket, 
    Error_ListenSocket, Error_AcceptSocket, Error_ReceiveData, Error_SendData
};

class BaseSocket {
private:
    WSADATA wsaData;
    ErrorID _error;
    void ThrowError(ErrorID _error);
public:
    BaseSocket();
    ~BaseSocket();
};

};

#endif