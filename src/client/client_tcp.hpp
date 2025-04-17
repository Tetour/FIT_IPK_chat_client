#pragma once

#include "client.hpp"

class ClientTCP : public Client {
public:
    ClientTCP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries);
    ~ClientTCP();

    bool connect() override;
    bool disconnect() override;
    bool sendMessage(const std::string& message) override;
    bool receiveMessage(std::string& message) override;
    void run() override;
};