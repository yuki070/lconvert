/*
 * luawrapper.h
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#ifndef LUAWRAPPER_H_
#define LUAWRAPPER_H_

extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}
#include <string>
#include <map>
#include <vector>

class LuaWrapper {
public:
    static LuaWrapper *getInstance();

    void openLib(const std::string &libName);
    void openAllLibs();
    void executeFile(const std::string &filePath);
    void setGlobalTable(const std::string &tableName,
            std::map<std::string, std::string>::const_iterator begin,
            std::map<std::string, std::string>::const_iterator end);

    void getGlobal(std::string globalSymbol);
    void call(int nargs, int nresults);
    void pushTable(std::vector<std::string> array);
    std::vector<std::string> popTable();

    static const char* LUA_LIB_BASE;
    static const char* LUA_LIB_COROUTINE;
    static const char* LUA_LIB_TABLE;
    static const char* LUA_LIB_IO;
    static const char* LUA_LIB_OS;
    static const char* LUA_LIB_STRING;
    static const char* LUA_LIB_BIT32;
    static const char* LUA_LIB_MATH;
    static const char* LUA_LIB_DEBUG;
    static const char* LUA_LIB_PACKAGE;
protected:
    LuaWrapper();
    virtual ~LuaWrapper();
    static LuaWrapper *luaHandler;
    lua_State *_luaState;
};

#endif /* LUAWRAPPER_H_ */
