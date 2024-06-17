#ifndef SOCKET_H
#define SOCKET_H

#include "winsock2.h"
#include "ws2tcpip.h"

namespace WEBSERVER{

enum ErrorID;

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