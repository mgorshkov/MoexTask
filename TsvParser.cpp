#include "TsvParser.h"

TsvParser::TsvParser(std::istream& aStream)
    : mIsValid(false)
    , mIsHeaderParsed(false)
    , mStream(aStream)
{
}

std::vector<std::string> Split(const std::string& str, char sep = '\t')
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(sep);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(sep, start);
    }

    r.push_back(str.substr(start));

    return r;
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
    if (!mIsValid)
        return nullptr;

    if (!mIsHeaderParsed)
        ParseHeader();

    std::string line;        
    // data
    if (!std::getline(mStream, line))
        return nullptr;

    auto strs = Split(line);
    return std::make_unique<Data>(strs[mColumns[0]], std::atoi(strs[mColumns[1]].c_str()));
}
