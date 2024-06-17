#include "winsock2.h"
#include "ws2tcpip.h"
#include <iostream>
#include <string>
#include <vector>

    //获取主机名
std::vector<std::string> getLocalIPAddresses() {
    std::vector<std::string> ipAddresses;
    char hostname[256];

    // 获取主机名
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        std::cerr << "Error getting hostname: " << WSAGetLastError() << std::endl;
        return ipAddresses;
    }

    // 获取主机地址信息
    addrinfo hints = {};
    hints.ai_family = AF_INET; // 仅获取IPv4地址
    addrinfo* addrInfo;
    if (getaddrinfo(hostname, nullptr, &hints, &addrInfo) != 0) {
        std::cerr << "Error getting address info: " << WSAGetLastError() << std::endl;
        return ipAddresses;
    }

    // 遍历地址信息
    for (addrinfo* ptr = addrInfo; ptr != nullptr; ptr = ptr->ai_next) {
        sockaddr_in* sockaddr_ipv4 = reinterpret_cast<sockaddr_in*>(ptr->ai_addr);
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sockaddr_ipv4->sin_addr), ipStr, INET_ADDRSTRLEN);
        ipAddresses.push_back(ipStr);
    }

    freeaddrinfo(addrInfo);
    return ipAddresses;
}




int main() {
    std::cout << "this is Server windows\n";
    
    //初始化网络库
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize\n";
        return 1;
    }
    std::cout << "wsadata\n";

    //创建套接字socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket\n";
        WSACleanup();
        return 1;
    }
    std::cout << "socket\n";

    // 绑定套接字
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(32140);
    // serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_addr.S_un.S_addr = INADDR_ANY;
    // const char* IPv4 = "10.181.71.241";
    // if (inet_pton(AF_INET, IPv4, &(serverAddress.sin_addr)) <= 0) {
    //     std::cerr << "无效服务器地址\n";
    //     closesocket(listenSocket);
    //     WSACleanup();
    //     return 1;
    // }


    std::vector<std::string> ipAddresses = getLocalIPAddresses();

    // 输出所有IP地址
    for (const std::string& ip : ipAddresses) {
        std::cout << "Local IP Address: " << ip << std::endl;
    }
    


    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddress),
    sizeof(serverAddress)) == SOCKET_ERROR) {
        std::cerr << "Failed to bind socket.\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "bindsocket\n";

    // 设置监听状态
    if (listen(listenSocket, 5) == SOCKET_ERROR) {
        std::cerr << "Failed to listen socket\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "listensocket\n";

    // 等待接收
    SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
    // clientsocket位于服务器端，用于与对应客户端通信
    // 服务端的serversocket本身并不处理请求，而是额外创建socket处理
    std::cout << "acceptsocket\n";

    while (true) {
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Failed to accept client\n";
            closesocket(listenSocket);
            WSACleanup();
            return 1;
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

    closesocket(listenSocket);
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}