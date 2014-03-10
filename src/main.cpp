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
#include "luawrapper.h"
#include "stringutil.h"

int main(int argc, char *argv[]) {
    try {
        Context *context = Context::getInstance();
        context->init(argc, argv);

        LuaWrapper *luaHandler = LuaWrapper::getInstance();
        luaHandler->openAllLibs();
        luaHandler->executeFile(context->getLuaFilePath());
        luaHandler->setGlobalTable("Env", context->getParamsBegin(), context->getParamsEnd());

        std::ifstream input(context->getInputFilePath().c_str());
        if (!input) {
            std::cout << context->getInputFilePath() << ": Open file error." << std::endl;
            return 1;
        }
        std::ofstream output(context->getOutputFilePath().c_str());
        if (!output) {
            std::cout << context->getOutputFilePath() << ": Open file error." << std::endl;
            return 1;
        }

        std::string line;
        while (getline(input, line)) {
            std::vector<std::string> fields = stringutil::split(context->getSeparator(), line);
            luaHandler->getGlobal("conv");
            luaHandler->pushTable(fields);
            luaHandler->call(1, 1);
            // getResult
            std::vector<std::string> outArr = luaHandler->popTable();
            for (size_t i = 0; i < outArr.size(); i++) {
                output << outArr[i];
                if ((i + 1) != outArr.size()) {
                    output << context->getSeparator();
                }
            }
            output << std::endl;
        }
        output.close();
        input.close();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        return 1;
    }
    return 0;
}

