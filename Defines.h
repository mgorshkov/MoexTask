#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <iomanip>

using EventName = std::string;
using ResponseTime = int;

using Times = std::map<ResponseTime, long long>;

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
            << "ResponseTime=" << aData.mAvgTsMr;
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
        
    return stream;
}

using DataQueue = std::queue<DataPtr>;
using DataSet = std::multiset<ResponseTime>;
using Log = std::unordered_map<EventName, DataSet>;

struct EventStatistics
{
    int mMin; // min – Минимальное время ответа на транзакцию в микросекундах
    int mMedian; // - 50% - Медиана
    int m90; // - 90% - 90% результатов меньше 122 микросекунд
    int m99; // - 99% - 99% результатов меньше 140 микросекунд
    int m999; // - 99.9% - 99.9% результатов меньше 145 микросекунд

    inline friend std::ostream& operator << (std::ostream& stream, const EventStatistics& aStatistics)
    {
        stream << "min=" << aStatistics.mMin << " "
            << "50%=" << aStatistics.mMedian << " "
            << "90%=" << aStatistics.m90 << " "
            << "99%=" << aStatistics.m99 << " "
            << "99.9%=" << aStatistics.m999 << std::endl;
        return stream;
    }
};

using EventStatisticsVector = std::vector<EventStatistics>;

inline std::ostream& operator << (std::ostream& stream, const EventStatisticsVector& aStatisticsVector)
{
    for (const auto& eventStat : aStatisticsVector)
        stream << eventStat;

    return stream;
}

struct TotalStatistics
{
    int mExecTime; // Время ответа на транзакцию, кратное 5 микросекундам
    long mTransNo; // Количество транзакций с таким временем
    double mWeight; // Процент от общего количества транзакций
    double mPercent; // Процент от общего количества транзакций, имеющих время ответа <= EXECTIME

    inline friend std::ostream& operator << (std::ostream& stream, const TotalStatistics& aStatistics)
    {
        stream << aStatistics.mExecTime << " "
            << aStatistics.mTransNo << " "
            << std::setw(2) << std::fixed << std::setprecision(2) << aStatistics.mWeight << " "
            << std::setw(2) << std::fixed << std::setprecision(2) << aStatistics.mPercent << std::endl;
        return stream;
    }
};

using TotalStatisticsVector = std::vector<TotalStatistics>;

inline std::ostream& operator << (std::ostream& stream, const TotalStatisticsVector& aStatistics)
{
    stream << "ExecTime TransNo Weight,% Percent" << std::endl;

    for (const auto& totalStat : aStatistics)
        stream << totalStat;

    return stream;
}
