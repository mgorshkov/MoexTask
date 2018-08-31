#include <optional>
#include <string>

class CommandLineParser
{
public:
    CommandLineParser(int aArgc, char** aArgv);

    std::optional<std::string> GetOption(const std::string& mName);

private:
    int mArgc;
    char** mArgv;
};

