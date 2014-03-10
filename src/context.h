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
    typedef std::map<std::string, std::string>::iterator ParamIterator;
    static Context *getInstance();
    void Init(int argc, char *argv[]);

    std::string GetLuaFilePath() const {
        return _luaFile;
    }

    std::string GetInputFilePath() const {
        return _inFile;
    }

    std::string GetOutputFilePath() const {
        return _outFile;
    }

    ParamIterator GetParamsBegin() {
        return _params.begin();
    }

    ParamIterator GetParamsEnd() {
        return _params.end();
    }

    std::string GetSeparator() const {
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
};

#endif /* CONTEXT_H_ */
