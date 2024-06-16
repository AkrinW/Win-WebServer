#include "winsock2.h"
#include <iostream>
// #pragma comment(lib, WS2_32)

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return 1;
    }
    // 你的网络编程代码
    WSACleanup();
    return 0;
}