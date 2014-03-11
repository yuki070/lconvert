/*
 * luahelper.h
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#ifndef LUAWRAPPER_H_
#define LUAHELPER_H_

extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}
#include <string>
#include <map>
#include <vector>

class LuaHelper {
public:
    typedef std::vector<std::string>::const_iterator VectorIterator;
    typedef std::map<std::string, std::string>::const_iterator MapIterator;
public:
    enum LibType {
        LUA_LIB_BASE,
        LUA_LIB_COROUTINE,
        LUA_LIB_TABLE,
        LUA_LIB_IO,
        LUA_LIB_OS,
        LUA_LIB_STRING,
        LUA_LIB_BIT32,
        LUA_LIB_MATH,
        LUA_LIB_DEBUG,
        LUA_LIB_PACKAGE,
    };

    LuaHelper();
    virtual ~LuaHelper();
    void OpenLib(LibType libType);
    void OpenAllLibs();
    void ExecuteFile(const std::string &filePath);
    void SetGlobalMap(const std::string &tableName, MapIterator begin,
            MapIterator end);
    void LocateGlobalSymbol(const std::string &globalSymbol);
    void LocateGlobalFunction(const std::string &globalSymbol);
    void Call(int nargs, int nresults);
    void PushVector(VectorIterator begin, VectorIterator end);
    void PushMap(MapIterator begin, MapIterator end);
    std::vector<std::string> PopVector();
protected:
    static int panicFunc(lua_State *L);
    lua_State *_luaState;
};

#endif /* LUAWRAPPER_H_ */
