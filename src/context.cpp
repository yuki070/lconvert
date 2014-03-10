/*
 * context.cpp
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#include <stdlib.h>
#include <iostream>
#include "context.h"
#include "config.h"     // Create by autotools

Context::Context() {
}

Context::~Context() {
}

Context *Context::context;

void Context::usage() {
    std::cout << PACKAGE_STRING << std::endl;
    std::cout << "Bug report to: " << PACKAGE_BUGREPORT << std::endl;
    std::cout << "Usage: " << PACKAGE << " <luaFile> <inputFile> <outputFile> [-p pname pvalue]" << std::endl;
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

void Context::Init(int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        exit(1);
    }
    _luaFile    = argv[1];
    _inFile     = argv[2];
    _outFile    = argv[3];
    for (int i = 4; i < (argc - 2); i = i + 3) {
        if (std::string(argv[i]) != "-p") {
            usage();
            exit(1);
        }
        std::string pname(argv[i + 1]);
        std::string pvalue(argv[i + 2]);
        _params.insert(std::pair<std::string, std::string>(pname, pvalue));
    }
    if (_params.find("SEPARATOR") == _params.end()) {
        _params.insert(std::pair<std::string, std::string>("SEPARATOR", "&&"));  // add default separator
    }
    _separator = _params["SEPARATOR"];
}
