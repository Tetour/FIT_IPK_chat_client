#pragma once

#include <string>
#include <cstdint>

class Client {
public:
    Client(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries);
    virtual ~Client();

    virtual bool connect() = 0;
    virtual bool disconnect() = 0;
    virtual bool sendMessage(const std::string& message) = 0;
    virtual bool receiveMessage(std::string& message) = 0;
    virtual void run() = 0;

protected:
    std::string serverAddress;
    uint16_t serverPort;
    uint16_t timeout;
    uint16_t maxRetries;
};
