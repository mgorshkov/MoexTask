#include <optional>
#include <string>

class CommandLineParser
{
public:
    CommandLineParser(int argc, char** argv);

    std::optional<std::string> GetOption(const std::string& mName);
};

