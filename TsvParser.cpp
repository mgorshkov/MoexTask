#include "TsvParser.h"

TsvParser::TsvParser(std::istream& aStream)
    : mIsValid(false)
    , mStream(aStream)
{
    ParseHeader();
}

std::vector<std::string> Split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void TsvParser::ParseHeader(std::iostream& aStream)
{
    std::string line;
    // header
    std::getline(stream, line);

    auto strs = Split(line);

    for (std::size_t i = 0; i < mColumnCount; ++i)
    {
        mColumns[i] = -1;
        for (std::size_t j = 0; j < strs.size(), ++j)
        {
            if (strs[j] == ColumnNames[i].mName)
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
}

DataPtr TsvParser::Produce() const
{
    if (!mIsValid())
        return nullptr;

    std::string line;        
    // data
    if (!std::getline(mStream, line))
        return nullptr;

    auto strs = Split(line);
    return std::make_unique<Data>(strs[columns[0]], std::atoi(strs[columns[1]]));
}
