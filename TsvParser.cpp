#include "TsvParser.h"

const TsvParser::ColumnName TsvParser::mColumnsNames =
{
    { Column::TIME, "TIME" },
    { Column::EVENT, "EVENT" },
    { Column::CALLCNT, "CALLCNT" },
    { Column::FILLCNT, "FILLCNT" },
    { Column::AVGSIZE, "AVGSIZE" },
    { Column::MAXSIZE, "MAXSIZE" },
    { Column::AVGFULL, "AVGFULL" },
    { Column::MAXFULL, "MAXFULL" },
    { Column::MINFULL, "MINFULL" },
    { Column::AVGDLL, "AVGDLL" },
    { Column::MAXDLL, "MAXDLL" },
    { Column::AVGTRIP, "AVGTRIP" },
    { Column::MAXTRIP, "MAXTRIP" },
    { Column::AVGTEAP, "AVGTEAP" },
    { Column::MAXTEAP, "MAXTEAP" },
    { Column::AVGTSMR, "AVGTSMR" },
    { Column::MAXTSMR, "MAXTSMR" },
    { Column::MINTSMR, "MINTSMR" }
};

Data TsvParser::GetData() const
{
    return mData;
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

void TsvParser::Parse(std::iostream& aStream)
{
    std::string line;
    // header
    std::getline(stream, line);

    auto strs = Split(line);

    if (strs.size() != Size)
    {
        std::cerr << "Incorrect stream format" << std::endl;
        return;
    }

    std::size_t surnameIndex, roleIndex;
    std::vector <std::wstring> columns = { L"Фамилия", L"Специальность" };
    if (strs[0] == columns[0] && strs[1] == columns[1])
    {
        surnameIndex = 0;
        roleIndex = 1;
    }
    else if (strs[0] == columns[1] && strs[1] == columns[0])
    {
        surnameIndex = 1;
        roleIndex = 0;
    }
    else
    {
        std::wcerr << L"Неверный формат, файл " << aPath.wstring() << L", пропускаем" << std::endl;
        return;
    }

    while (std::getline(stream, line))
    {
        auto strs = Split(line);
        if (strs.size() != 2)
        {
            std::wcerr << L"Неверный формат, файл " << aPath.wstring() << L", строка " << line << L", пропускаем" << std::endl;
            continue;
        }

        auto department = aPath.stem().wstring();
        mEmployees.insert({department, strs[surnameIndex], strs[roleIndex]});
    }
}
