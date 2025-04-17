#include "parser.hpp"


using namespace std;


Parser::Parser() {

}

Parser::~Parser() {

}

bool Parser::AreArgsValid(int argc, char ** argv){
    bool tFlag = false; 
    bool sFlag = false;

    if((argc == 2 && string(argv[1]) == "-h")){
        cout << "IPK25-CHAT Client Usage:"                                     << endl;
        cout << "  -t <tcp|udp>    Transport protocol"                         << endl;
        cout << "  -s <IP/host>    Server address"                             << endl;
        cout << "  -p <port>       Server port (default: 4567)"                << endl;
        cout << "  -d <ms>         UDP confirmation timeout (default: 250ms)"  << endl;
        cout << "  -r <count>      Maximum UDP retransmissions (default: 3)"   << endl;
        cout << "  -h              Print help message"                         << endl;
        return true;
    }

    for(int i = 0; i < argc; i++){
        if (string(argv[i]) == "-t") { 
            if(!(i+1 < argc && CheckProtocol(argv[i+1]))){
                return false;
            }
            protocol = string(argv[i+1]);
            tFlag = true;
            i++;
        }
        else if(string(argv[i]) == "-s"){
            if(!(i+1 < argc && CheckServerAddress(argv[i+1]))){
                return false;
            }
            serverAddress = string(argv[i+1]);
            sFlag = true;
            i++;
        }
        else if(string(argv[i]) == "-p"){ 
            if (!(i+1 < argc && CheckPortValidity(argv[i+1]))){
                return false;
            }
            serverPort = static_cast<uint16_t>(strtol(argv[i+1], nullptr, 10));
            i++;
        }
        else if(string(argv[i]) == "-d"){
            if (!(i+1 < argc && CheckNum(argv[i+1]))){
                return false;
            }
            timeout = static_cast<uint16_t>(strtol(argv[i+1], nullptr, 10));
            i++;
        }
        else if(string(argv[i]) == "-r"){
            if (!(i+1 < argc && CheckNum(argv[i+1]))){
                return false;
            }
            maxRetries = static_cast<uint16_t>(strtol(argv[i+1], nullptr, 10));
            i++;
        }
    }

    if(!tFlag || !sFlag){ // t and s options are compulsory
        return false;
    }
    return true;
}

string Parser::GetProtocol() const {
    return protocol;
}

string Parser::GetServerAddress() const {
    return serverAddress;
}

uint16_t Parser::GetServerPort() const {
    return serverPort;
}

uint16_t Parser::GetTimeout() const {
    return timeout;
}

uint16_t Parser::GetMaxRetries() const {
    return maxRetries;
}

bool Parser::IsHelp() const {
    return helpFlag;
}

bool Parser::CheckProtocol(char* argv){
    if((string(argv) == "tcp") || (string(argv) == "udp")){
        return true;
    }
    return false;
}

bool Parser::CheckServerAddress(char* address) {
    // Try IPv4 address validation
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, address, &(sa.sin_addr));

    if (result == 1) {
        return true;
    } else if (result == -1) {
        return false;
    }
    
    // Try hostname validation
    // RFC 1123 compliant hostname pattern
    static const regex hostname_pattern(
        "^(?!-)[A-Za-z0-9-]{1,63}(?<!-)"      // Label
        "(?:\\.[A-Za-z0-9-]{1,63}(?<!-)){0,}" // Additional labels
        "\\.?"                                // Optional trailing dot
        "$"
    );
    
    string hostname(address);
    if (!regex_match(hostname, hostname_pattern)) {
        return false;
    }
    
    // Try to resolve the hostname
    struct addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;        // IPv4 only
    hints.ai_socktype = SOCK_STREAM;  // TCP socket
    
    int gai_result = getaddrinfo(address, nullptr, &hints, &res);
    if (gai_result != 0) {
        return false;   // DNS resolution failed
    }

    freeaddrinfo(res);
    return true;
}
    
bool Parser::CheckPortValidity(char* port){
    char* end;
    unsigned long value = strtol(port, &end, 10);
    
    // Check if conversion was successful and within range
    if (*end != '\0' || value > 65535) {
        return false;
    }

    return true;
}

bool Parser::CheckNum(char* value){
    char* end;
    strtol(value, &end, 10);

    // Check if conversion was successful
    if (*end != '\0') {
        return false;
    }

    return true;
}


