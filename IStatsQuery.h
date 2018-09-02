#pragma once

#include <vector>
#include "Defines.h"

class IStatsQuery
{
public:
    virtual ~IStatsQuery() = default;

    virtual std::vector<Statistics> AllStats() const = 0;
    virtual Statistics StatsByEvent(const EventName& aEvent) const = 0;
};
