/*
 * context.cpp
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "context.h"
#include "stringutil.h"
#include "config.h"     // Create by autotools

Context::Context() {
}

Context::~Context() {
}

const char* Context::DEFAULT_SEPARATOR = "&&";
Context *Context::context = 0;

void Context::usage() {
    std::cout << PACKAGE_STRING << std::endl;
    std::cout << "Bug report to: " << PACKAGE_BUGREPORT << std::endl;
    std::cout << "Usage: " << PACKAGE << " <luaFile> <inputFile> <outputFile> [-p \"pname=pvalue\"]" << std::endl;
    std::cout << std::endl;
    std::cout << "-p  Add a custom parameter which is named 'pname' and with value of 'pvalue'." << std::endl;
    std::cout << "    You can add more than one parameter. These parameters will put into a table" << std::endl;
    std::cout << "    (Env) in lua. You can use in lua like thie: Env['pname']. It will return pvalue to you." << std::endl;
}

Context *Context::getInstance() {
    if (!context) {
        context = new Context();
    }
    return context;
}

void Context::init(int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        exit(1);
    }
    _luaFile    = argv[1];
    _inFile     = argv[2];
    _outFile    = argv[3];
    int opt;
    std::vector<std::string> parts;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
        case 'p':
            std::cout << optind << std::endl;
            parts = stringutil::split("=", argv[optind - 1]);
            _params.insert(std::pair<std::string, std::string>(parts[0], parts[1]));
            break;
        default:
            usage();
            exit(1);
        }
    }
    if (_params.find("SEPARATOR") == _params.end()) {
        _params.insert(
                std::pair<std::string, std::string>("SEPARATOR",
                        DEFAULT_SEPARATOR));  // add default separator
    }
    _separator = _params["SEPARATOR"];
}
