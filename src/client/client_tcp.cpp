#include "client_tcp.hpp"

#include <iostream>
#include <algorithm>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
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
    // Check if socket is valid and close it
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
    // TCP message receiving implementation
    return true;
}

void ClientTCP::run() {
    if (!connect()) {
        cerr << "ERROR: Failed to connect to server" << endl;
        return;
    }

    string message;
    while (getline(cin, message)) {
        if (!sendMessage(message)) {
            cerr << "ERROR: Failed to send message" << endl;
            break;
        }

        string response;
        if (!recvMessage(response)) {
            cerr << "ERROR: Failed to receive response" << endl;
            break;
        }
    }

    disconnect();
}

string ClientTCP::createMessageMsg(string messageContent) const {
    return "MSG FROM " + dname + " IS " + messageContent + "\r\n";
}

string ClientTCP::createMessageErr(string messageContent) const {
    return "ERR FROM " + dname + " IS " + messageContent + "\r\n";
}

string ClientTCP::createMessageJoin(string channelID) const {
    return "JOIN " + channelID + " AS " + dname + "\r\n";
}

string ClientTCP::createMessageAuth() const {
    return "AUTH " + userId + " AS " + dname + " USING " + secret + "\r\n";
}

string ClientTCP::createMessageBye() const {
    return "BYE FROM " + dname + "\r\n";
}
