#include "client.hpp"
#include <algorithm>
#include <cctype>

Client::Client(std::string serverAddress, uint16_t serverPort) {
    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
}

Client::~Client() {
}

bool Client::setUserId(const std::string& userId) {
    if (!isIdValid(userId)) {
        return false;
    }
    this->userId = userId;
    return true;
}

bool Client::setDname(const std::string& dname) {
    if (!isDnameValid(dname)) {
        return false;
    }
    this->dname = dname;
    return true;
}

bool Client::setSecret(const std::string& secret) {
    if (!isSecretValid(secret)) {
        return false;
    }
    this->secret = secret;
    return true;
}

bool Client::isIdValid(const std::string& id) const {
    // Check length (1-20 characters)
    if (id.empty() || id.length() > 20) {
        return false;
    }

    // Check each character is alphanumeric, underscore or hyphen
    return std::all_of(id.begin(), id.end(), [](char c) {
        return std::isalnum(c) || c == '_' || c == '-';
    });
}

bool Client::isSecretValid(const std::string& secret) const {
    // Check length (1-128 characters)
    if (secret.empty() || secret.length() > 128) {
        return false;
    }

    // Check each character is alphanumeric, underscore or hyphen
    return std::all_of(secret.begin(), secret.end(), [](char c) {
        return std::isalnum(c) || c == '_' || c == '-';
    });
}

bool Client::isDnameValid(const std::string& dname) const {
    // Check length (1-20 characters)
    if (dname.empty() || dname.length() > 20) {
        return false;
    }

    // Check each character is a printable character (0x21-7E)
    return std::all_of(dname.begin(), dname.end(), [](char c) {
        return c >= 0x21 && c <= 0x7E;
    });
}

bool Client::isContentValid(const std::string& messageContent) const {
    // Check length (1-60000 characters)
    if (messageContent.empty() || messageContent.length() > 60000) {
        return false;
    }

    // Check each character is a printable character, space, or line feed (0x0A,0x20-7E)
    return std::all_of(messageContent.begin(), messageContent.end(), [](char c) {
        return c == 0x0A || (c >= 0x20 && c <= 0x7E);
    });
}