#include "client_tcp.hpp"
#include <iostream>

ClientTCP::ClientTCP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries) 
    : Client(serverAddress, serverPort, timeout, maxRetries) {
}

ClientTCP::~ClientTCP() {
    disconnect();
}

bool ClientTCP::connect() {
    // TCP connection implementation
    return true;
}

bool ClientTCP::disconnect() {
    // TCP disconnection implementation
    return true;
}

bool ClientTCP::sendMessage(const std::string& message) {
    // TCP message sending implementation
    return true;
}

bool ClientTCP::receiveMessage(std::string& message) {
    // TCP message receiving implementation
    return true;
}

void ClientTCP::run() {
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