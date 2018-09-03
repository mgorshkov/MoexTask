#include <regex>

#include "TsvParser.h"

TsvParser::TsvParser(std::istream& aStream)
    : mIsValid(false)
    , mIsHeaderParsed(false)
    , mStream(aStream)
{
}

std::vector<std::string> Split(const std::string& str)
{
    std::vector<std::string> result;
    static std::regex pattern{R"(\s+)"};
    std::copy(std::sregex_token_iterator(str.begin(), str.end(), pattern, -1),
        std::sregex_token_iterator(), std::back_inserter(result));
    return result;
}

void TsvParser::ParseHeader()
{
    std::string line;
    // header
    std::getline(mStream, line);

    auto strs = Split(line);

    for (std::size_t i = 0; i < mColumnCount; ++i)
    {
        mColumns[i] = -1;
        for (std::size_t j = 0; j < strs.size(); ++j)
        {
            if (strs[j] == mColumnNames[i].mName)
                mColumns[i] = j;
        }
    }

    for (std::size_t i = 0; i < mColumnCount; ++i)
    {
        if (mColumns[i] == -1)
        {
            std::cerr << "Incorrect stream format" << std::endl;
            mIsValid = false;
            break;
        }
    }

    mIsValid = true;
    mIsHeaderParsed = true;
}

DataPtr TsvParser::Produce()
{
    if (!mIsHeaderParsed)
        ParseHeader();

    if (!mIsValid)
        return nullptr;

    std::string line;
    // data
    if (!std::getline(mStream, line))
        return nullptr;

    auto strs = Split(line);
    if (strs.size() < std::max(mColumns[0], mColumns[1]) + 1)
    {
        std::cerr << "Incorrect stream format" << std::endl;
        mIsValid = false;
        return nullptr;
    }

    return std::make_unique<Data>(strs[mColumns[0]], std::atoi(strs[mColumns[1]].c_str()));
}
