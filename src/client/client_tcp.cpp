#include "client_tcp.hpp"

#include <iostream>
#include <algorithm>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

using namespace std;

ClientTCP::ClientTCP(string serverAddress, uint16_t serverPort) 
    : Client(serverAddress, serverPort) {
}

ClientTCP::~ClientTCP() {
    disconnect();
}

bool ClientTCP::connect() {
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        cerr << "ERROR: Failed to create socket" << endl;
        return false;
    }

    // Specify address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverAddress.c_str());

    // Send connection request
    if (::connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "ERROR: Failed to connect to server" << endl;
        close(sockfd);
        sockfd = -1;
        return false;
    }

    return true;
}

bool ClientTCP::disconnect() {
    // Close socket if it is valid
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
    return true;
}

bool ClientTCP::sendMessage(const string& message) {
    ssize_t bytesSent = send(sockfd, message.c_str(), message.length(), 0);
    if (bytesSent == -1) {
        cerr << "ERROR: Failed to send message" << endl;
        return false;
    }
    return true;
}

bool ClientTCP::recvMessage(string& message) {
    char buffer[60004]; // Maximum message size (60000) + extra for headers/terminators
    message.clear();
    
    // Read until we find \r\n or error occurs
    while (true) {
        ssize_t bytesReceived = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0) {
                // Connection closed by server
                cerr << "ERROR: Server closed connection" << endl;
            } else {
                cerr << "ERROR: Failed to receive message" << endl;
            }
            return false;
        }
        
        buffer[bytesReceived] = '\0';
        message += buffer;
        
        // Check if we have a complete message
        if (message.find("\r\n") != string::npos) {
            return true;
        }
    }
}

void ClientTCP::run() {
    if (!connect()) {
        cerr << "ERROR: Failed to connect to server" << endl;
        return;
    }

    struct pollfd polls[2];
    
    // Watch server socket for input
    polls[0].fd = sockfd;
    polls[0].events = POLLIN;
    
    // Watch stdin for input
    polls[1].fd = STDIN_FILENO;
    polls[1].events = POLLIN;

    string response;
    string input;
    bool running = true;

    while (running) {
        // Wait for events with 5 second timeout
        int ret = poll(polls, 2, 5000);
        
        if (ret == -1) {
            if (errno == EINTR) {
                // Interrupted by signal, continue
                continue;
            }
            cerr << "ERROR: Poll failed" << endl;
            break;
        }

        // Check for socket input
        if (polls[0].revents & POLLIN) {
            if (!recvMessage(response)) {
                cerr << "ERROR: Failed to receive response" << endl;
                break;
            }
            cout << "Received: " << response;
        }

        // Check for user input
        if (polls[1].revents & POLLIN) {
            if (!getline(cin, input)) {
                // EOF or error
                break;
            }
            
            if (!input.empty()) {
                string msg = createMessageMsg(input);
                if (!sendMessage(msg)) {
                    cerr << "ERROR: Failed to send message" << endl;
                    break;
                }
            }
        }
    }

    disconnect();
}

string ClientTCP::createMessageMsg(const string & messageContent) const {
    return "MSG FROM " + dname + " IS " + messageContent + "\r\n";
}

string ClientTCP::createMessageErr(const string & messageContent) const {
    return "ERR FROM " + dname + " IS " + messageContent + "\r\n";
}

string ClientTCP::createMessageJoin(const string & channelID) const {
    return "JOIN " + channelID + " AS " + dname + "\r\n";
}

string ClientTCP::createMessageAuth() const {
    return "AUTH " + userId + " AS " + dname + " USING " + secret + "\r\n";
}

string ClientTCP::createMessageBye() const {
    return "BYE FROM " + dname + "\r\n";
}
