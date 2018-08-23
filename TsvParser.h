#pragma once

#include <iostream>

#include "Defines.h"

class TsvParser
{
public:
    TsvParser(std::istream& aStream);

    Data GetData() const;

private:
    void Parse(std::istream& aStream);

    Data mData;

    enum class Column
    {
        TIME,
        EVENT,
        CALLCNT,
        FILLCNT,
        AVGSIZE,
        MAXSIZE,
        AVGFULL,
        MAXFULL,
        MINFULL,
        AVGDLL,
        MAXDLL,
        AVGTRIP,
        MAXTRIP,
        AVGTEAP,
        MAXTEAP,
        AVGTSMR,
        MAXTSMR,
        MINTSMR,
        Size
    };

    struct ColumnNames
    {
        Column mColumn;
        const char* mName;
    };

    static const ColumnName mColumnsNames;
};
