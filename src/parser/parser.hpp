#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <regex>
#include <string>
#include <cstring>
#include <netdb.h>
#include <arpa/inet.h>


class Parser {
public:
    Parser();
   ~Parser();

    bool AreArgsValid(int argc, char ** argv);

    std::string GetProtocol() const;
    std::string GetServerAddress() const;
    uint16_t GetServerPort() const;
    uint16_t GetTimeout() const;
    uint8_t GetMaxRetries() const;

    bool IsHelp() const;

private:
    std::string protocol;
    std::string serverAddress;
    uint16_t serverPort = 4567;
    uint16_t timeout = 250;     // timeout in milliseconds
    uint8_t maxRetries = 3;

    bool helpFlag = false;

    bool CheckProtocol(char* argv);
    bool CheckServerAddress(char* address);
    bool CheckNum(char* value);
    bool CheckPortValidity(char* port); 
};