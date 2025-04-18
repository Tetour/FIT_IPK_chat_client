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

    bool recvMessage(std::string& message) override;
    bool sendMessage(const std::string& message) override;

    std::string createMessageMsg  (std::string messageContent ) const;
    std::string createMessageErr  (std::string messageContent ) const;
    std::string createMessageJoin (std::string channelID      ) const;
    std::string createMessageAuth () const;
    std::string createMessageBye  () const;

private:
    int sockfd = -1;
};