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

void usage() {
    std::cout << "lconvert <luaFile> <inputFile> <outputFile> [-p pname pvalue]" << std::endl;
    std::cout << std::endl;
    std::cout << "-p  Add a custom parameter which is named 'pname' and with value of 'pvalue'." << std::endl;
    std::cout << "    You can add more than one parameter. These parameters will put into a table" << std::endl;
    std::cout << "    (Env) in lua. You can use in lua like thie: Env['pname']. It will return pvalue to you." << std::endl;
}

std::vector<std::string> split(const char * sep, const std::string& str) {   
    std::vector<std::string> v;
    size_t sep_len = strlen(sep);
    size_t p1 = 0;
    size_t p2 = 0;
    do {
        p2 = str.find(sep, p1);
        v.push_back(str.substr(p1, p2 - p1));
        p1 = p2 + sep_len;
    } while (p2 != std::string::npos);
    return v;
}

int main (int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        return 1;
    }
    std::string luaFile(argv[1]);
    std::string inputFile(argv[2]);
    std::string outputFile(argv[3]);
    std::map<std::string, std::string> params;
    for (int i = 4; i < (argc - 2); i = i + 3) {
        if (std::string(argv[i]) != "-p") {
            usage();
            return 1;
        }
        std::string pname(argv[i + 1]);
        std::string pvalue(argv[i + 2]);
        params.insert(std::pair<std::string, std::string>(pname, pvalue));
    }

    try {
        lua_State *L;
        L = luaL_newstate();
        luaL_openlibs(L);

        if (luaL_dofile(L, luaFile.c_str()) != 0) {
            std::cout << luaFile.c_str() << ": Open file error." << std::endl;
            return 1;
        }
        // push Env
        lua_newtable(L);
        for (std::map<std::string, std::string>::iterator i = params.begin();
                i != params.end(); i++) {
            lua_pushstring(L, i->first.c_str());
            lua_pushstring(L, i->second.c_str());
            lua_settable(L, -3);
        }
        lua_setglobal(L, "Env");

        std::ifstream input(inputFile.c_str());
        if (!input) {
            std::cout << inputFile << ": Open file error." << std::endl;
            return 1;
        }
        std::ofstream output(outputFile.c_str());
        if (!output) {
            std::cout << outputFile << ": Open file error." << std::endl;
            return 1;
        }

        std::string line;
        while (getline(input, line)) {
            std::vector<std::string> fields = split("&&", line);
            lua_getglobal(L, "conv");
            //// push IN line
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
            } else {
                size_t tableSize = lua_rawlen(L, -1);
                for (int i = 0; i < tableSize; i++) {
                    lua_pushinteger(L, i + 1);
                    lua_gettable(L, -2);
                    output << lua_tostring(L, -1) << "&&";
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

