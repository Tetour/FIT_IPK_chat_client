#include "client_udp.hpp"
#include <iostream>

ClientUDP::ClientUDP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries) 
    : Client(serverAddress, serverPort, timeout, maxRetries) {
}

ClientUDP::~ClientUDP() {
    disconnect();
}

bool ClientUDP::connect() {
    // UDP connection implementation
    return true;
}

bool ClientUDP::disconnect() {
    // UDP disconnection implementation
    return true;
}

bool ClientUDP::sendMessage(const std::string& message) {
    // UDP message sending implementation
    return true;
}

bool ClientUDP::receiveMessage(std::string& message) {
    // UDP message receiving implementation
    return true;
}

void ClientUDP::run() {
    if (!connect()) {
        throw std::runtime_error("Failed to connect to server");
    }

    std::string message;
    while (std::getline(std::cin, message)) {
        if (!sendMessage(message)) {
            throw std::runtime_error("Failed to send message");
        }

        std::string response;
        if (!receiveMessage(response)) {
            throw std::runtime_error("Failed to receive response");
        }
    }

    disconnect();
}