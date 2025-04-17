#include "parser/parser.hpp"
#include "client/client.hpp"
#include "client/client_udp.hpp"
#include "client/client_tcp.hpp"

#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    Parser parser;
    
    if (!parser.AreArgsValid(argc, argv)) {
        return 1;
    } else if (parser.IsHelp()) {
        return 0;
    }

    try {
        if (parser.GetProtocol() == "tcp") {
            ClientTCP client(
                parser.GetServerAddress(),
                parser.GetServerPort(),
                parser.GetTimeout(),
                parser.GetMaxRetries()
            );
            client.run();
        } else {
            ClientUDP client(
                parser.GetServerAddress(),
                parser.GetServerPort(),
                parser.GetTimeout(),
                parser.GetMaxRetries()
            );
            client.run();
        }
    } catch (const std::exception& error) {
        cerr << "Error: " << error.what() << endl;
        return 1;
    }
    return 0;
}