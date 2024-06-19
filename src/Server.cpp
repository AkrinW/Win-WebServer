#include "Server.h"
#include <iostream>

namespace WEBSERVER {

BaseServer::BaseServer(int p): port(p) {
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    // serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr),
    sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket.\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "bindsocket\n";

    // 设置监听状态
    if (listen(listenSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Failed to listen socket\n";
        exit(EXIT_FAILURE);
    }
    std::cout << "listensocket\n";

    // 等待接收
    clientSocket = accept(listenSocket, nullptr, nullptr);
    // clientsocket位于服务器端，用于与对应客户端通信
    // 服务端的serversocket本身并不处理请求，而是额外创建socket处理
    std::cout << "acceptsocket\n";
}

BaseServer::~BaseServer() {
    closesocket(listenSocket);
    closesocket(clientSocket);
}

void BaseServer::Run() {
    while (true) {
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept client\n";
            exit(EXIT_FAILURE);
        }
        
        char revBuffer[1024] = "";
        if (recv(clientSocket, revBuffer, sizeof(revBuffer), 0)
        == SOCKET_ERROR) {
            std::cerr << "Failed to receive data\n";
            closesocket(clientSocket);
            continue;
        }
        std::cout << "receive client: " << revBuffer << '\n';
        std::string message = "server: hello client\n";
        if (send(clientSocket, message.c_str(), message.size(), 0)
        == SOCKET_ERROR) {
            std::cout << "Failed to send data\n";
        }
    }
}


void BaseServer::_GetIPAddress() {
    char hostname[256];

    // 获取主机名
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "Error getting hostname: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 获取主机地址信息
    addrinfo hints = {};
    hints.ai_family = AF_INET; // 仅获取IPv4地址
    addrinfo* addrInfo;
    if (getaddrinfo(hostname, nullptr, &hints, &addrInfo) != 0) {
        std::cerr << "Error getting address info: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }

    // 遍历地址信息
    for (addrinfo* ptr = addrInfo; ptr != nullptr; ptr = ptr->ai_next) {
        sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipStr, INET_ADDRSTRLEN);
        IPAddress.push_back(ipStr);
    }

    freeaddrinfo(addrInfo);


}

std::string BaseServer::GetIPAddress() {
    if (IPAddress.empty()) {
        _GetIPAddress();
    }
    return IPAddress[0];
}


};