/*
 * logger.cpp
 *
 *  Created on: 2014Äê3ÔÂ11ÈÕ
 *      Author: liangjianqiang
 */

#include <stdlib.h>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include "logger.h"
#include "context.h"
#include "config.h"

Logger::Logger() {
#ifdef _HAS_LOG4CPP
    logger = 0;
#endif
}

Logger::~Logger() {
#ifdef _HAS_LOG4CPP
    if (logger) {
        delete logger;
        logger = 0;
    }
#endif
}

void Logger::Init() {
#ifdef _HAS_LOG4CPP
    try {
        logger = new writelog_t(PACKAGE);
    } catch (std::exception &e) {
        throw std::runtime_error(std::string("Open log file error: ") + e.what());
    }
#else
    std::string logFilePath(std::string(getenv("BIPROG_ROOT")) + "/log/" + PACKAGE + ".log");
    logStream.open(logFilePath.c_str());
    if (!logStream.good()) {
        throw std::runtime_error("Open log file error");
    }
#endif
}

void Logger::WriteFile(const std::string &msg) {
#ifdef _HAS_LOG4CPP
    logger->info(formatMessage(msg).c_str());
#else
    logStream << formatMessage(msg) << std::endl;
#endif
}

void Logger::WriteTerminal(const std::string &msg) {
    std::cout << formatMessage(msg) << std::endl;
}

std::string Logger::formatMessage(const std::string &msg) {
    static char szTimeStr[32];
    struct tm *local;
    time_t current_time;
    time(&current_time);
    local = localtime(&current_time);
    memset(szTimeStr, 0, sizeof(szTimeStr));
    strftime(szTimeStr, 30, "%Y-%m-%d %H:%M:%S", local);

    Context *ctx = Context::getInstance();
    std::ostringstream oss;
    oss << "[" << szTimeStr << "][PID = " << ctx->Pid() << "] " << msg;
    return oss.str();
}
