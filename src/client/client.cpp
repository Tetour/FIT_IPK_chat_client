#include "client.hpp"

Client::Client(std::string serverAddress, uint16_t serverPort) {
    this->serverAddress = serverAddress;
    this->serverPort = serverPort;
}

Client::~Client() {

}