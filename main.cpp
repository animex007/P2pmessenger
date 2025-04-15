// === File: main.cpp ===
#include <winsock2.h>
#include <iostream> // <-- Added for std::cerr and std::endl
#include "ui.h"
#include "peer.h"
#include "discovery.h"
#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return 1;
    }

    initDiscovery();
    startServer(); // Starts TCP server
    runUI();       // Starts GUI loop

    WSACleanup();
    return 0;
}
