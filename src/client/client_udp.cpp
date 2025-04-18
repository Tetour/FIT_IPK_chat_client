#include "client_udp.hpp"
#include <iostream>


ClientUDP::ClientUDP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint8_t maxRetries) 
    : Client(serverAddress, serverPort), timeout(timeout), maxRetries(maxRetries) {
}

ClientUDP::~ClientUDP() {
    disconnect();
}

bool ClientUDP::connect(){
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
        std::cerr << "ERROR: Failed to connect to server" << std::endl;
        return;
    }

    std::string message;
    while (std::getline(std::cin, message)) {
        if (!sendMessage(message)) {
            std::cerr << "ERROR: Failed to send message" << std::endl;
            break;
        }

        std::string response;
        if (!receiveMessage(response)) {
            std::cerr << "ERROR: Failed to receive response" << std::endl;
            break;
        }
    }

    disconnect();
}