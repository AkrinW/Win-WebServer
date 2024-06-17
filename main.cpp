#include "winsock2.h"
#include "ws2tcpip.h"
#include <iostream>
// #pragma comment(lib, WS2_32)

int main() {
    //初始化网络库
    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
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
    std::cout << "lisensocket\n";
    // 绑定套接字
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
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to accept client connect\n";
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    // clientsocket位于服务器端，用于与对应客户端通信
    // 服务端的serversocket本身并不处理请求，而是额外创建socket处理
    std::cout << "acceptsocket\n";

    // 接收数据
    std::string buffer;
    int bytesRead = recv(clientSocket, &buffer[0], sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        std::cerr << "Failed to receive data\n";
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    buffer = '\0';
    std::cout << "recvsocket\n";

    // 发送数据
    std::string message = "Hello client\n";
    std::cout << message;
    if (send(clientSocket, &message[0], message.size(), 0)
    == SOCKET_ERROR) {
        std::cerr << "Failed to send data\n";
        closesocket(clientSocket);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "sendsocket\n";

    // 连接服务器（客户端函数）
    SOCKET sockfd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(32140);

    if (inet_pton(AF_INET, "IP", &(serverAddr.sin_addr)) <= 0) {
        std::cerr << "无效服务器地址\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    if (connect(sockfd, reinterpret_cast<sockaddr*>(&serverAddr),
    sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server\n";
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    std::cout << "connectserver\n";

    // 关闭套接字
    closesocket(clientSocket);
    closesocket(listenSocket);

    WSACleanup();//释放Winsock资源，并通知系统不再需要动态连接库函数
    return 0;
}