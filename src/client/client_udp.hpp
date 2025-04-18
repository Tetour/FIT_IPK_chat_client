#pragma once

#include "client.hpp"
#include <string>
#include <vector>
#include <netinet/in.h>

class ClientUDP : public Client {
public:
    ClientUDP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint8_t maxRetries);
    ~ClientUDP();

    bool connect() override;
    bool disconnect() override;
    void run() override;
    bool sendMessage(const std::string& message) override;
    bool receiveMessage(std::string& message) override;

private:
    uint16_t timeout;
    uint8_t maxRetries;
};