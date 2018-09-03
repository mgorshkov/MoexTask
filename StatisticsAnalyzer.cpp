#include "StatisticsAnalyzer.h"

StatisticsAnalyzer::StatisticsAnalyzer(Synchronizer& aSynchronizer)
    : mSynchronizer(aSynchronizer)
{
}

static int Round(ResponseTime aTime, ResponseTime aMultiple)
{
    return ((aTime + aMultiple / 2) / aMultiple) * aMultiple;
}

void StatisticsAnalyzer::Consume(DataPtr&& aData)
{
    if (mSynchronizer.IsStopped())
        return;

    mEvents[aData->mEvent].insert(aData->mAvgTsMr);
    ++mTimes[Round(aData->mAvgTsMr, Multiplier)];
}

EventStatisticsVector StatisticsAnalyzer::EventStats() const
{
    EventStatisticsVector statistics;
    for (const auto& event : mEvents)
        statistics.push_back(EventStats(event.first));
    return statistics;
}

EventStatistics StatisticsAnalyzer::EventStats(const EventName& aEvent) const
{
    EventStatistics statistics{0};
#ifdef DEBUG_PRINT
    std::cout << "EventStats for " << aEvent << " " << aEvent.length() << std::endl;
#endif
    auto eventsIt = mEvents.find(aEvent);
    if (eventsIt != mEvents.end())
    {
        auto CalcStats = [&eventsIt](double percent)
        {
            auto timesIt = eventsIt->second.begin();
            std::advance(timesIt, eventsIt->second.size() * percent);
            return *timesIt;
        };
        statistics.mMin = *eventsIt->second.begin();
        statistics.mMedian = CalcStats(0.5);
        statistics.m90 = CalcStats(0.9);
        statistics.m99 = CalcStats(0.99);
        statistics.m999 = CalcStats(0.999);
    }
    return statistics;
}

TotalStatisticsVector StatisticsAnalyzer::TotalStats() const
{
    TotalStatisticsVector statistics;
    auto size = mTimes.size();
    double prevPercent = 0.0;
    for (const auto& time : mTimes)
    {
        TotalStatistics stats;
        stats.mExecTime = time.first;
        stats.mTransNo = time.second;
        stats.mWeight = static_cast<double>(time.second) / size * 100;
        stats.mPercent = stats.mWeight + prevPercent;
        prevPercent = stats.mPercent;

        statistics.push_back(stats);
    }
    return statistics;
}
