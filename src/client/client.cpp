#include "client.hpp"


Client::Client(std::string serverAddress, uint16_t serverPort, uint16_t timeout, uint16_t maxRetries) {
    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
    this->timeout = timeout;
    this->maxRetries = maxRetries;
}

Client::~Client() {

}