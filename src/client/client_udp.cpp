#include "client_udp.hpp"
#include <iostream>


ClientUDP::ClientUDP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint8_t maxRetries) 
    : Client(serverAddress, serverPort), timeout(timeout), maxRetries(maxRetries) {
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

bool ClientUDP::recvMessage(std::string& message) {
    // UDP message receiving implementation
    return true;
}

void ClientUDP::run() {
    // UDP client run implementation
    return;
}

std::string ClientUDP::createMessageMsg(std::string messageContent) const {
    // TODO: Implement UDP protocol message format
    return "";
}

std::string ClientUDP::createMessageErr(std::string messageContent) const {
    // TODO: Implement UDP protocol message format
    return "";
}

std::string ClientUDP::createMessageJoin(std::string channelID) const {
    // TODO: Implement UDP protocol message format
    return "";
}

std::string ClientUDP::createMessageAuth() const {
    // TODO: Implement UDP protocol message format
    return "";
}

std::string ClientUDP::createMessageBye() const {
    // TODO: Implement UDP protocol message format
    return "";
}