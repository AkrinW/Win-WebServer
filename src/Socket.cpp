#include "Socket.h"
#include <iostream>

namespace WEBSERVER{

BaseSocket::BaseSocket() {
    _error = NoError;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        _error = Error_InitWSA;
        ThrowError(_error);
    }
}

void BaseSocket::ThrowError(WEBSERVER::ErrorID _error) {
    switch (_error) {
    case Error_InitWSA:
        std::cerr << "Failed to Initialize\n";
        exit(EXIT_FAILURE);
    default:
        break;
    }
}

BaseSocket::~BaseSocket() {
    WSACleanup();
}

};