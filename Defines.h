#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <set>
#include <unordered_map>

using EventName = std::string;
using ResponseTime = int;

struct Data
{
    Data(const std::string& aEvent, int aAvgTsMr)
        : mEvent(aEvent)
        , mAvgTsMr(aAvgTsMr)
    {
    }
    EventName mEvent;
    ResponseTime mAvgTsMr;

    inline friend std::ostream& operator << (std::ostream& stream, const Data& aData)
    {
        stream << "EventName=" << aData.mEvent << " "
            << "ResponseTime=" << aData.mAvgTsMr << " " << std::endl;
        return stream;
    }
};

using DataPtr = std::unique_ptr<Data>;

inline std::ostream& operator << (std::ostream& stream, const DataPtr& aData)
{
    if (aData)
        stream << *aData;
    else
        stream << "null";
        
    stream << std::endl;
    return stream;
}

using DataQueue = std::queue<DataPtr>;
using DataSet = std::multiset<ResponseTime>;
using Log = std::unordered_map<EventName, DataSet>;

struct Statistics
{
    int mMin; // min – Минимальное время ответа на транзакцию в микросекундах
    int mMedian; // - 50% - Медиана
    int m90; // - 90% - 90% результатов меньше 122 микросекунд
    int m99; // - 99% - 99% результатов меньше 140 микросекунд
    int m999; // - 99.9% - 99.9% результатов меньше 145 микросекунд

    inline friend std::ostream& operator << (std::ostream& stream, const Statistics& aStatistics)
    {
        stream << "min=" << aStatistics.mMin << " "
            << "50%=" << aStatistics.mMedian << " "
            << "90%=" << aStatistics.m90 << " "
            << "99%=" << aStatistics.m99 << " "
            << "99.9%=" << aStatistics.m999 << std::endl;
        return stream;
    }
};
