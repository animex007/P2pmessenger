#include "discovery.h"
#include "peer.h"
#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <set>
#pragma comment(lib, "ws2_32.lib")

std::set<std::string> discoveredPeers;

void listenForPeers() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(9001);

    bind(sock, (sockaddr*)&addr, sizeof(addr));

    while (true) {
        char buffer[1024];
        sockaddr_in sender;
        int len = sizeof(sender);
        int n = recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr*)&sender, &len);
        if (n > 0) {
            std::string ip = inet_ntoa(sender.sin_addr);
            if (discoveredPeers.insert(ip).second) {
                std::cout << "[Discovered peer at: " << ip << "]\n";
                connectToPeer(ip);
            }
        }
    }
}

void sendDiscoveryBroadcast() {
    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    BOOL broadcast = TRUE;
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, sizeof(broadcast));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9001);
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    while (true) {
        const char* msg = "DISCOVER";
        sendto(sock, msg, strlen(msg), 0, (sockaddr*)&addr, sizeof(addr));
        Sleep(5000);
    }
}

void initDiscovery() {
    std::thread(listenForPeers).detach();
    std::thread(sendDiscoveryBroadcast).detach();
}
