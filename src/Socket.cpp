#include "Socket.h"
#include <iostream>

namespace WEBSERVER{

enum ErrorID {
    NoError, Error_InitWSA, Error_CreatSocket, Error_InvalidAddr, Error_BindSocket, 
    Error_ListenSocket, Error_AcceptSocket, Error_ReceiveData, Error_SendData
};

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