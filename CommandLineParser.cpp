#include "CommandLineParser.h"

CommandLineParser::CommandLineParser(int aArgc, char** aArgv)
    : mArgc(aArgc)
    , mArgv(aArgv)
{
}

std::optional<std::string> CommandLineParser::GetOption(const std::string& mName)
{
    for (int i = 0; i < mArgc; ++i)
    {
        std::string arg{mArgv[i]};
        std::string pattern = "-" + mName + "=";
        auto index = arg.find(pattern);
        if (index == 0)
            return arg.substr(index + pattern.length(), arg.length());
    }
    return std::optional<std::string>{};
}


