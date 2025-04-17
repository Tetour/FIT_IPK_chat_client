#pragma once

#include "client.hpp"

class ClientUDP : public Client {
public:
    ClientUDP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries);
    ~ClientUDP();

    bool connect() override;
    bool disconnect() override;
    bool sendMessage(const std::string& message) override;
    bool receiveMessage(std::string& message) override;
    void run() override;
};