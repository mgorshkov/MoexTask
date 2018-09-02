#pragma once

#include <string>
#include <memory>
#include <queue>
#include <vector>

struct Data
{
    Data(const std::string& aEvent, int aAvgTsMr)
        : mEvent(aEvent)
        , mAvgTsMr(aAvgTsMr)
    {
    }
    std::string mEvent;
    int mAvgTsMr;
};

using DataPtr = std::unique_ptr<Data>;
using DataQueue = std::queue<DataPtr>;

using Log = std::vector<DataPtr>;

struct Statistics
{
    int mMin; // min – Минимальное время ответа на транзакцию в микросекундах
    int mMedian; // - 50% - Медиана
    int m90; // - 90% - 90% результатов меньше 122 микросекунд
    int m99; // - 99% - 99% результатов меньше 140 микросекунд
    int m999; // - 99.9% - 99.9% результатов меньше 145 микросекунд
};


