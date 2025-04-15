#ifndef PEER_H
#define PEER_H

void startServer();

#endif // PEER_H
#pragma once
#include <string>
void startServer();
void connectToPeer(const std::string& ip);
void broadcastMessage(const std::string& msg);
