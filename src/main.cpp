#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
extern "C" {
#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"
}

#include "context.h"

std::vector<std::string> split(const std::string& sep, const std::string& str) {
    std::vector<std::string> v;
    size_t sep_len = sep.length();
    size_t p1 = 0;
    size_t p2 = 0;
    do {
        p2 = str.find(sep, p1);
        v.push_back(str.substr(p1, p2 - p1));
        p1 = p2 + sep_len;
    } while (p2 != std::string::npos);
    return v;
}

int main(int argc, char *argv[]) {
    try {
        Context *context = Context::getInstance();
        context->Init(argc, argv);

        lua_State *L;
        L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_dofile(L, context->GetLuaFilePath().c_str()) != 0) {
            std::cout << context->GetLuaFilePath() << ": Open file error." << std::endl;
            return 1;
        }
        // push Env
        lua_newtable(L);
        for (Context::ParamIterator i = context->GetParamsBegin();
                i != context->GetParamsEnd(); i++) {
            lua_pushstring(L, i->first.c_str());
            lua_pushstring(L, i->second.c_str());
            lua_settable(L, -3);
        }
        lua_setglobal(L, "Env");

        std::ifstream input(context->GetInputFilePath().c_str());
        if (!input) {
            std::cout << context->GetInputFilePath() << ": Open file error." << std::endl;
            return 1;
        }
        std::ofstream output(context->GetOutputFilePath().c_str());
        if (!output) {
            std::cout << context->GetOutputFilePath() << ": Open file error." << std::endl;
            return 1;
        }

        std::string line;
        while (getline(input, line)) {
            std::vector<std::string> fields = split(context->GetSeparator(), line);
            lua_getglobal(L, "conv");
            // push IN line
            lua_newtable(L);
            for (int i = 0; i < fields.size(); i++) {
                lua_pushnumber(L, i + 1);
                lua_pushstring(L, fields[i].c_str());
                lua_settable(L, -3);
            }
            lua_call(L, 1, 1);  // call lua function
            // getResult
            if (lua_istable(L, -1) != 1) {
                std::cout << "return is not table" << std::endl;
                return 1;
            } else {
                size_t tableSize = lua_rawlen(L, -1);
                for (int i = 1; i <= tableSize; i++) {
                    lua_pushinteger(L, i);
                    lua_gettable(L, -2);
                    output << lua_tostring(L, -1);
                    if (i != tableSize) {
                        output << context->GetSeparator();
                    }
                    lua_pop(L, 1);
                }
                output << std::endl;
                lua_pop(L, 1);
            }
        }
        output.close();
        input.close();
        lua_close(L);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        return 1;
    }
    return 0;
}

