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
    bool recvMessage(std::string& message) override;

    std::string createMessageMsg  (std::string messageContent) const override;
    std::string createMessageErr  (std::string messageContent) const override;
    std::string createMessageJoin (std::string channelID     ) const override;
    std::string createMessageAuth () const override;
    std::string createMessageBye  () const override;

private:
    uint16_t timeout;
    uint8_t maxRetries;
};