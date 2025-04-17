#include "client_tcp.hpp"


ClientTCP::ClientTCP(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries) 
    : Client(serverAddress, serverPort, timeout, maxRetries) {
}

ClientTCP::~ClientTCP() {
    disconnect();
}

bool ClientTCP::connect() {
    struct addrinfo hints = {}, *serverInfo, *p;
    hints.ai_family = AF_INET;        // IPv4
    hints.ai_socktype = SOCK_STREAM;  // TCP
    hints.ai_protocol = IPPROTO_TCP;

    // Convert port number to string
    std::string portStr = std::to_string(serverPort);

    // Get server address info
    int rv = getaddrinfo(serverAddress.c_str(), portStr.c_str(), &hints, &serverInfo);
    if (rv != 0) {
        std::cerr << "ERROR: " << gai_strerror(rv) << std::endl;
        return false;
    }

    // Try each address until we successfully connect
    for(p = serverInfo; p != nullptr; p = p->ai_next) {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd == -1) {
            continue;
        }

        if (::connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            sockfd = -1;
            continue;
        }

        break; // Successfully connected
    }

    freeaddrinfo(serverInfo);

    if (sockfd == -1) {
        std::cerr << "ERROR: Failed to connect to server: " << strerror(errno) << std::endl;
        return false;
    }

    // Set socket timeout if specified
    if (timeout > 0) {
        struct timeval tv;
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;

        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
            std::cerr << "ERROR: Failed to set receive timeout: " << strerror(errno) << std::endl;
            return false;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv)) < 0) {
            std::cerr << "ERROR: Failed to set send timeout: " << strerror(errno) << std::endl;
            return false;
        }
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
        throw std::runtime_error("Failed to connect to server");
    }

    std::string message;
    while (std::getline(std::cin, message)) {
        if (!sendMessage(message)) {
            throw std::runtime_error("Failed to send message");
        }

        std::string response;
        if (!receiveMessage(response)) {
            throw std::runtime_error("Failed to receive response");
        }
    }

    disconnect();
}