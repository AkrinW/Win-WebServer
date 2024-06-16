#include "winsock2.h"
#include <iostream>
// #pragma comment(lib, WS2_32)

int main() {
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        WSACleanup();
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(32140);
    serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddress),
    sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    WSACleanup();
    return 0;
}