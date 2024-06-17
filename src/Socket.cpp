#include "Socket.h"

namespace WEBSERVER{

BaceSocket::BaceSocket() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize\n";
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

BaceSocket::~BaceSocket() {
    WSACleanup();
}

};