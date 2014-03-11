/*
 * luahelper.cpp
 *
 *  Created on: 2014Äê3ÔÂ10ÈÕ
 *      Author: liangjianqiang
 */

#include <stdexcept>
#include "luahelper.h"

int LuaHelper::panicFunc(lua_State *L) {
    throw std::runtime_error("Error in lua");
}

LuaHelper::LuaHelper() {
    _luaState = luaL_newstate();
    lua_atpanic(_luaState, panicFunc);
}

LuaHelper::~LuaHelper() {
    if (_luaState) {
        lua_close(_luaState);
        _luaState = 0;
    }
}

void LuaHelper::OpenLib(LibType libType) {
    switch (libType) {
    case LUA_LIB_BASE:
        luaopen_base(_luaState);
        break;
    case LUA_LIB_COROUTINE:
        luaopen_coroutine(_luaState);
        break;
    case LUA_LIB_TABLE:
        luaopen_table(_luaState);
        break;
    case LUA_LIB_IO:
        luaopen_io(_luaState);
        break;
    case LUA_LIB_OS:
        luaopen_os(_luaState);
        break;
    case LUA_LIB_STRING:
        luaopen_string(_luaState);
        break;
    case LUA_LIB_BIT32:
        luaopen_bit32(_luaState);
        break;
    case LUA_LIB_MATH:
        luaopen_math(_luaState);
        break;
    case LUA_LIB_DEBUG:
        luaopen_debug(_luaState);
        break;
    case LUA_LIB_PACKAGE:
        luaopen_package(_luaState);
        break;
    default:
        throw std::runtime_error("Unkonw lib type.");
    }
}

void LuaHelper::OpenAllLibs() {
    luaL_openlibs(_luaState);
}

void LuaHelper::ExecuteFile(const std::string &filePath) {
    luaL_dofile(_luaState, filePath.c_str());
}

void LuaHelper::SetGlobalMap(const std::string &tableName, MapIterator begin,
        MapIterator end) {
    PushMap(begin, end);
    lua_setglobal(_luaState, tableName.c_str());
}

void LuaHelper::LocateGlobalSymbol(const std::string &globalSymbol) {
    lua_getglobal(_luaState, globalSymbol.c_str());
}

void LuaHelper::LocateGlobalFunction(const std::string &globalSymbol) {
    LocateGlobalSymbol(globalSymbol);
}

void LuaHelper::Call(int nargs, int nresults) {
    lua_call(_luaState, nargs, nresults);
}

void LuaHelper::PushVector(VectorIterator begin, VectorIterator end) {
    lua_newtable(_luaState);
    size_t j = 1;
    for (VectorIterator p = begin; p != end; p++, j++) {
        lua_pushnumber(_luaState, j);
        lua_pushstring(_luaState, p->c_str());
        lua_settable(_luaState, -3);
    }
}

void LuaHelper::PushMap(MapIterator begin, MapIterator end) {
    lua_newtable(_luaState);
    for (MapIterator i = begin; i != end; i++) {
        lua_pushstring(_luaState, i->first.c_str());
        lua_pushstring(_luaState, i->second.c_str());
        lua_settable(_luaState, -3);
    }
}

std::vector<std::string> LuaHelper::PopVector() {
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
