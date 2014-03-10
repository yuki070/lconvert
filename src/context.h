/*
 * context.h
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <map>

class Context {
public:
    typedef std::map<std::string, std::string>::const_iterator ParamIterator;
    static Context *getInstance();
    void init(int argc, char *argv[]);

    std::string getLuaFilePath() const {
        return _luaFile;
    }

    std::string getInputFilePath() const {
        return _inFile;
    }

    std::string getOutputFilePath() const {
        return _outFile;
    }

    ParamIterator getParamsBegin() const {
        return _params.begin();
    }

    ParamIterator getParamsEnd() const {
        return _params.end();
    }

    std::string getSeparator() const {
        return _separator;
    }
protected:
    static void usage();
    Context();
    virtual ~Context();

    static Context *context;

    std::string _luaFile;
    std::string _inFile;
    std::string _outFile;
    std::string _separator;
    std::map<std::string, std::string> _params;

public:
    static const char* DEFAULT_SEPARATOR;
};

#endif /* CONTEXT_H_ */
