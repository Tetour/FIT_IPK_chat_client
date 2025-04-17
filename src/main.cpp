#include "parser/parser.hpp"

#include <iostream>


int main(int argc, char ** argv) {
    Parser parser;
    
    if (!parser.AreArgsValid(argc, argv)) {
        return 1;
    } else if (parser.IsHelp()) {
        return 0;
    }

    return 0;
}