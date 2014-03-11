/*
 * context.h
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <unistd.h>
#include <map>

class Context {
public:
    typedef std::map<std::string, std::string>::const_iterator ParamIterator;
    typedef std::map<std::string, std::string>::value_type ParamType;
public:
    static const char* DEFAULT_SEPARATOR;
    static const char* PARAM_NAME_SEPARATOR;
    static const char* STR_EQ;

    static Context *getInstance();

    void Init(int argc, char *argv[]);

    std::string LuaFilePath() const {
        return _luaFile;
    }

    std::string InputFilePath() const {
        return _inFile;
    }

    std::string OutputFilePath() const {
        return _outFile;
    }

    ParamIterator CustomParamsBegin() const {
        return _params.begin();
    }

    ParamIterator CustomParamsEnd() const {
        return _params.end();
    }

    std::string Separator() const {
        return _separator;
    }

    pid_t Pid() const {
        return _pid;
    }
protected:
    Context();
    virtual ~Context();

    static Context *instance;
    static void usage();

    std::string _luaFile;
    std::string _inFile;
    std::string _outFile;
    std::string _separator;
    std::map<std::string, std::string> _params;
    pid_t _pid;
};

#endif /* CONTEXT_H_ */
