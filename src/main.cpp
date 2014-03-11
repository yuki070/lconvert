#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "context.h"
#include "luahelper.h"
#include "stringutil.h"
#include "logger.h"

#include "config.h"

int main(int argc, char *argv[]) {
    try {
        Context *context = Context::getInstance();
        context->Init(argc, argv);
        Logger logger;
        logger.Init();
        logger.WriteFileAndTerminal(
                std::string(PACKAGE) + "[" + VERSION + "] Script["
                        + context->LuaFilePath() + "] Input["
                        + context->InputFilePath() + "] -> Start Convert...");

        LuaHelper lua;
        lua.OpenAllLibs();
        lua.ExecuteFile(context->LuaFilePath());
        lua.SetGlobalMap("Env", context->CustomParamsBegin(), context->CustomParamsEnd());

        std::ifstream iStream(context->InputFilePath().c_str());
        if (!iStream) {
            throw std::runtime_error(context->InputFilePath() + ": Open file error.");
        }
        std::ofstream oStream(context->OutputFilePath().c_str());
        if (!oStream) {
            throw std::runtime_error(context->OutputFilePath() + ": Open file error.");
        }

        std::string line;
        while (getline(iStream, line)) {
            std::vector<std::string> fields = stringutil::Split(context->Separator(), line);
            lua.LocateGlobalFunction("conv");
            lua.PushVector(fields.begin(), fields.end());
            lua.Call(1, 1);
            // getResult
            std::vector<std::string> outArr = lua.PopVector();
            for (size_t i = 0; i < outArr.size(); i++) {
                oStream << outArr[i];
                if ((i + 1) != outArr.size()) {
                    oStream << context->Separator();
                }
            }
            oStream << std::endl;
        }
        oStream.close();
        iStream.close();
        logger.WriteFileAndTerminal(std::string("Convert finish."));
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknow exception." << std::endl;
        return 1;
    }
    return 0;
}

