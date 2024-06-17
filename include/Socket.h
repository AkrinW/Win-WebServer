#ifndef SOCKET_H
#define SOCKET_H

#include "winsock2.h"
#include "ws2tcpip.h"
#include <iostream>
#include <string>
#include <vector>

namespace WEBSERVER{

class BaceSocket {
private:
    WSADATA wsaData;
public:
    BaceSocket();
    ~BaceSocket();
};

};

#endif