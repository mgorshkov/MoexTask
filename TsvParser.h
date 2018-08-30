#pragma once

#include <iostream>

#include "Defines.h"

class TsvParser
{
public:
    TsvParser(std::istream& aStream);

    DataPtr Produce() const override;

private:
    void ParseHeader(std::istream& aStream);

    bool mIsValid;
    std::istream& mStream;

    enum class Column
    {
        EVENT,
        AVGTSMR
    };

    struct ColumnNames
    {
        Column mColumn;
        const char* mName;
    };

    static const ColumnName mColumnsNames[];

    static constexpr columnCount = sizeof(ColumnNames) / sizeof(ColumNames[0]);
    std::array<columnCount> mColumns{-1};
};
