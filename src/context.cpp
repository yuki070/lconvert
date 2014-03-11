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

Context *Context::instance = 0;

Context *Context::getInstance() {
    if (instance == 0) {
        instance = new Context;
    }
    return instance;
}

Context::Context() : _pid(0) {
}

Context::~Context() {
}

const char* Context::DEFAULT_SEPARATOR = "&";
const char* Context::PARAM_NAME_SEPARATOR = "SEPARATOR";
const char* Context::STR_EQ = "=";

void Context::usage() {
    std::cout << PACKAGE_STRING << std::endl;
    std::cout << "Bug report to: " << PACKAGE_BUGREPORT << std::endl;
    std::cout << "Usage: " << PACKAGE << " <luaFile> <inputFile> <outputFile> [-p \"pname=pvalue\"]" << std::endl;
    std::cout << std::endl;
    std::cout << "-p  Add a custom parameter which is named 'pname' and with value of 'pvalue'." << std::endl;
    std::cout << "    You can add more than one parameter. These parameters will put into a table" << std::endl;
    std::cout << "    (Env) in lua. You can use in lua like thie: Env['pname']. It will return pvalue to you." << std::endl;
}

void Context::Init(int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        exit(1);
    }
    _luaFile    = argv[1];
    _inFile     = argv[2];
    _outFile    = argv[3];
    int opt;
    std::vector<std::string> parts;
    parts.reserve(2);
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
        case 'p':
            parts = stringutil::Split(STR_EQ, argv[optind - 1]);
            _params.insert(ParamType(parts[0], parts[1]));
            break;
        default:
            usage();
            exit(1);
        }
    }
    if (_params.find(PARAM_NAME_SEPARATOR) == _params.end()) {
        _params.insert(ParamType(PARAM_NAME_SEPARATOR, DEFAULT_SEPARATOR));  // add default separator
    }
    _separator = _params[PARAM_NAME_SEPARATOR];
    _pid = getpid();
}
