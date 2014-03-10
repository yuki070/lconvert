/*
 * luawrapper.cpp
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#include <stdexcept>
#include "luawrapper.h"

LuaWrapper::LuaWrapper() {
    _luaState = luaL_newstate();
}

LuaWrapper::~LuaWrapper() {
    lua_close(_luaState);
}

const char* LuaWrapper::LUA_LIB_BASE         = "base";
const char* LuaWrapper::LUA_LIB_COROUTINE    = "coroutine";
const char* LuaWrapper::LUA_LIB_TABLE        = "table";
const char* LuaWrapper::LUA_LIB_IO           = "io";
const char* LuaWrapper::LUA_LIB_OS           = "os";
const char* LuaWrapper::LUA_LIB_STRING       = "string";
const char* LuaWrapper::LUA_LIB_BIT32        = "bit32";
const char* LuaWrapper::LUA_LIB_MATH         = "math";
const char* LuaWrapper::LUA_LIB_DEBUG        = "debug";
const char* LuaWrapper::LUA_LIB_PACKAGE      = "package";

LuaWrapper *LuaWrapper::luaHandler = 0;

LuaWrapper *LuaWrapper::getInstance() {
    if (!luaHandler) {
        luaHandler = new LuaWrapper;
    }
    return luaHandler;
}

void LuaWrapper::openLib(const std::string &libName) {
    if (libName.compare(LUA_LIB_BASE) == 0) {
        luaopen_base(_luaState);
    } else if (libName.compare(LUA_LIB_COROUTINE) == 0) {
        luaopen_coroutine(_luaState);
    } else if (libName.compare(LUA_LIB_TABLE) == 0) {
        luaopen_table(_luaState);
    } else if (libName.compare(LUA_LIB_IO) == 0) {
        luaopen_io(_luaState);
    } else if (libName.compare(LUA_LIB_OS) == 0) {
        luaopen_os(_luaState);
    } else if (libName.compare(LUA_LIB_STRING) == 0) {
        luaopen_string(_luaState);
    } else if (libName.compare(LUA_LIB_BIT32) == 0) {
        luaopen_bit32(_luaState);
    } else if (libName.compare(LUA_LIB_MATH) == 0) {
        luaopen_math(_luaState);
    } else if (libName.compare(LUA_LIB_DEBUG) == 0) {
        luaopen_debug(_luaState);
    } else if (libName.compare(LUA_LIB_PACKAGE) == 0) {
        luaopen_package(_luaState);
    } else {
        throw std::runtime_error(libName + ": Unkonw lib name.");
    }
}

void LuaWrapper::openAllLibs() {
    luaL_openlibs(_luaState);
}

void LuaWrapper::executeFile(const std::string &filePath) {
    luaL_dofile(_luaState, filePath.c_str());
}

void LuaWrapper::setGlobalTable(const std::string &tableName,
        std::map<std::string, std::string>::const_iterator begin,
        std::map<std::string, std::string>::const_iterator end) {
    lua_newtable(_luaState);
    for (std::map<std::string, std::string>::const_iterator i = begin;
            i != end; i++) {
        lua_pushstring(_luaState, i->first.c_str());
        lua_pushstring(_luaState, i->second.c_str());
        lua_settable(_luaState, -3);
    }
    lua_setglobal(_luaState, tableName.c_str());
}

void LuaWrapper::getGlobal(std::string globalSymbol) {
    lua_getglobal(_luaState, globalSymbol.c_str());
}

void LuaWrapper::call(int nargs, int nresults) {
    lua_call(_luaState, nargs, nresults);
}

void LuaWrapper::pushTable(std::vector<std::string> array) {
    lua_newtable(_luaState);
    for (int i = 0; i < array.size(); i++) {
        lua_pushnumber(_luaState, i + 1);
        lua_pushstring(_luaState, array[i].c_str());
        lua_settable(_luaState, -3);
    }
}

std::vector<std::string> LuaWrapper::popTable() {
    std::vector<std::string> result;
    size_t tableSize = lua_rawlen(_luaState, -1);
    result.reserve(tableSize);
    for (int i = 1; i <= tableSize; i++) {
        lua_pushinteger(_luaState, i);
        lua_gettable(_luaState, -2);
        result.push_back(lua_tostring(_luaState, -1));
        lua_pop(_luaState, 1);
    }
    lua_pop(_luaState, 1);
    return result;
}
