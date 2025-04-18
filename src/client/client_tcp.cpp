#include "client_tcp.hpp"

#include <iostream>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>


using namespace std;


ClientTCP::ClientTCP(std::string serverAddress, uint16_t serverPort) 
    : Client(serverAddress, serverPort) {
}

ClientTCP::~ClientTCP() {
    disconnect();
}

bool ClientTCP::connect() {
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cerr << "ERROR: Failed to create socket" << std::endl;
        return false;
    }

    // Specify address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());

    // Send connection request
    if (::connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "ERROR: Failed to connect to server" << std::endl;
        close(sockfd);
        sockfd = -1;
        return false;
    }

    return true;
}

bool ClientTCP::disconnect() {
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
    return true;
}

bool ClientTCP::sendMessage(const std::string& message) {
    // TCP message sending implementation
    return true;
}

bool ClientTCP::receiveMessage(std::string& message) {
    // TCP message receiving implementation
    return true;
}

void ClientTCP::run() {
    if (!connect()) {
        std::cerr << "ERROR: Failed to connect to server" << std::endl;
        return;
    }

    std::string message;
    while (std::getline(std::cin, message)) {
        if (!sendMessage(message)) {
            std::cerr << "ERROR: Failed to send message" << std::endl;
            break;
        }

        std::string response;
        if (!receiveMessage(response)) {
            std::cerr << "ERROR: Failed to receive response" << std::endl;
            break;
        }
    }

    disconnect();
}