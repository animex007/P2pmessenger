#include "peer.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

extern std::vector<std::string> messageLog;
extern std::mutex logMutex;

std::vector<SOCKET> peerSockets;
std::mutex peerMutex;

void handleClient(SOCKET sock) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(sock, buffer, 1024, 0);
        if (len > 0) {
            std::string received = "[Peer]: " + std::string(buffer);
            std::cout << received << std::endl;
            std::lock_guard<std::mutex> lock(logMutex);
            messageLog.push_back(received);
        }
    }
}

void startServer() {
    std::thread([]() {
        SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(9000);

        bind(server_fd, (sockaddr*)&addr, sizeof(addr));
        listen(server_fd, 5);

        while (true) {
            sockaddr_in client_addr;
            int client_len = sizeof(client_addr);
            SOCKET client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);

            std::lock_guard<std::mutex> lock(peerMutex);
            peerSockets.push_back(client_fd);
            std::thread(handleClient, client_fd).detach();
        }
    }).detach();
}

void connectToPeer(const std::string& ip) {
    std::thread([ip]() {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(9000);
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

        if (connect(sock, (sockaddr*)&addr, sizeof(addr)) >= 0) {
            std::lock_guard<std::mutex> lock(peerMutex);
            peerSockets.push_back(sock);
            std::thread(handleClient, sock).detach();
            std::cout << "[Connected to " << ip << "]\n";
        }
    }).detach();
}

void broadcastMessage(const std::string& msg) {
    std::lock_guard<std::mutex> lock(peerMutex);
    for (SOCKET sock : peerSockets) {
        send(sock, msg.c_str(), msg.size(), 0);
    }
}