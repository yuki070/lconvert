/*
 * logger.h
 *
 *  Created on: 2014Äê3ÔÂ11ÈÕ
 *      Author: liangjianqiang
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#ifdef _HAS_LOG4CPP
#include <logger/writelog.h>
#else
#include <fstream>
#endif

class Logger {
public:
    Logger();
    virtual ~Logger();

    void Init();
    void WriteFile(const std::string &msg);
    void WriteTerminal(const std::string &msg);

    void WriteFileAndTerminal(const std::string &msg) {
        WriteFile(msg);
        WriteTerminal(msg);
    }
protected:
    std::string formatMessage(const std::string &msg);
#ifdef _HAS_LOG4CPP
    writelog_t *logger;
#else
    std::ofstream logStream;
#endif
};

#endif /* LOGGER_H_ */
