#pragma once

#include <string>
#include <memory>
#include <queue>
#include <vector>

struct Data
{
    std::string mEvent;
    int mAvgTsMr;
};

using DataPtr = std::unique_ptr<Data>;
using DataQueue = std::queue<DataPtr>;

using Log = std::vector<DataPtr>;