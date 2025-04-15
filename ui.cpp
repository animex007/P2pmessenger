#include "ui.h"
#include "peer.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <windows.h>

std::vector<std::string> messageLog;
std::mutex logMutex;

void runUI() {
    std::string msg;
    std::cout << "======================\n";
    std::cout << " P2P Messenger (Demo) \n";
    std::cout << "======================\n";
    std::cout << "Commands:\n";
    std::cout << "  /log   - Show message log\n";
    std::cout << "  /clear - Clear message log\n";
    std::cout << "  /exit  - Exit app\n\n";
    while (true) {
        std::getline(std::cin, msg);
        if (msg == "/log") {
            std::lock_guard<std::mutex> lock(logMutex);
            for (const auto& m : messageLog)
                std::cout << m << std::endl;
        } else if (msg == "/clear") {
            std::lock_guard<std::mutex> lock(logMutex);
            messageLog.clear();
            std::cout << "[Log cleared]\n";
        } else if (msg == "/exit") {
            std::exit(0);
        } else {
            broadcastMessage(msg);
            std::lock_guard<std::mutex> lock(logMutex);
            messageLog.push_back("[You]: " + msg);
        }
    }
}