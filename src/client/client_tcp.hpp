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
    
   void run() override;

private:

    bool connect    () override;
    bool disconnect () override;

    bool recvMessage(      std::string & message) override;
    bool sendMessage(const std::string & message) override;

    std::string createMessageMsg  (const std::string & messageContent ) const;
    std::string createMessageErr  (const std::string & messageContent ) const;
    std::string createMessageJoin (const std::string & channelID      ) const;
    std::string createMessageAuth () const;
    std::string createMessageBye  () const;

    int sockfd = -1;
};