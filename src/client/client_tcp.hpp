#pragma once

#include "client.hpp"

#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


class ClientTCP : public Client {
public:
    ClientTCP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries);
    ~ClientTCP();

    bool connect() override;
    bool disconnect() override;
    bool sendMessage(const std::string& message) override;
    bool receiveMessage(std::string& message) override;
    void run() override;

private:
    int sockfd = -1;
};