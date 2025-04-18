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
    ClientTCP(std::string serverAddress, uint16_t serverPort);
   ~ClientTCP();

    bool connect() override;
    bool disconnect() override;
    void run() override;

    bool receiveMessage(std::string& message) override;
    bool sendMessage(const std::string& message) override;

    bool sendMessageAuth();
    bool sendMessageJoin();
    bool sendMessageBye();
    bool sendMessageErr();

private:
    int sockfd = -1;
};