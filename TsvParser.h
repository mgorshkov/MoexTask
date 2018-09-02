#pragma once

#include <iostream>

#include "Defines.h"
#include "IProducer.h"

class TsvParser : public IProducer
{
public:
    TsvParser(std::istream& aStream);

    DataPtr Produce() const override;

private:
    void ParseHeader();

    bool mIsValid;
    bool mIsHeaderParsed;

    std::istream& mStream;

    enum class Column
    {
        EVENT,
        AVGTSMR
    };

    struct ColumnName
    {
        Column mColumn;
        const char* mName;
    };

    static constexpr ColumnName mColumnNames[] =
    {
        { Column::EVENT, "EVENT" },
        { Column::AVGTSMR, "AVGTSMR" }
    };

    static constexpr std::size_t mColumnCount = sizeof(mColumnNames) / sizeof(mColumnNames[0]);
    std::array<int, mColumnCount> mColumns;
};
