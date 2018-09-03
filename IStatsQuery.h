#pragma once

#include <vector>
#include "Defines.h"

class IStatsQuery
{
public:
    virtual ~IStatsQuery() = default;

    virtual EventStatisticsVector EventStats() const = 0;
    virtual EventStatistics EventStats(const EventName& aEvent) const = 0;

    virtual TotalStatisticsVector TotalStats() const = 0;
};
