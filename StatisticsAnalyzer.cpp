#include "StatisticsAnalyzer.h"

StatisticsAnalyzer::StatisticsAnalyzer(Synchronizer& aSynchronizer)
    : mSynchronizer(aSynchronizer)
{
}

void StatisticsAnalyzer::Consume(DataPtr&& aData)
{
    if (mSynchronizer.IsStopped())
        return;

    mEvents[aData->mEvent].insert(aData->mAvgTsMr);
}

std::vector<Statistics> StatisticsAnalyzer::AllStats() const
{
    std::vector<Statistics> statistics;
    for (const auto& event : mEvents)
        statistics.push_back(StatsByEvent(event.first));
    return statistics;
}

Statistics StatisticsAnalyzer::StatsByEvent(const EventName& aEvent) const
{
    Statistics statistics{0};
    auto eventsIt = mEvents.find(aEvent);
    if (eventsIt != mEvents.end())
    {
        statistics.mMin = *eventsIt->second.begin();
        auto CalcStats = [&eventsIt](double percent)
        {
            auto timesIt = eventsIt->second.begin();
            std::advance(timesIt, eventsIt->second.size() * 0.5);
            return *timesIt;
        };
        statistics.mMedian = CalcStats(0.5);
        statistics.m90 = CalcStats(0.9);
        statistics.m99 = CalcStats(0.99);
        statistics.m999 = CalcStats(0.999);
    }
    return statistics;
}


