#include "winsock2.h"
#include "ws2tcpip.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "this is Client windows\n";
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize\n";
        WSACleanup();
        return 1;
    }
    SOCKET clientSocket;
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(32140);
    std::string IPv4 = "10.181.71.241";
    if (inet_pton(AF_INET, &IPv4[0], &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "无效服务器地址\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr),
    sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "connectserver\n";

    while (true) {
        std::string message;
        std::cout << "Enter a message to send (or 'quit' to exit): ";
        std::getline(std::cin, message);
        if (message == "quit") {
            break;
        }
        if (send(clientSocket, &message[0], message.size(), 0)
        == SOCKET_ERROR) {
            std::cerr << "Failed to send data\n";
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }

        std::string revBuffer = "";
        if (recv(clientSocket, &revBuffer[0], sizeof(revBuffer), 0)
        == SOCKET_ERROR) {
            std::cerr << "Failed to receive data\n";
            closesocket(clientSocket);
            WSACleanup();
            return 1;
        }
        std::cout << "received message from server: " << revBuffer << '\n';
    }   
    closesocket(clientSocket);
    WSACleanup();



    return 0;
}