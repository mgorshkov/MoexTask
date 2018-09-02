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

void StatisticsAnalyzer::DumpStatistics()
{
    auto stats = AllStats();
    for (const auto& stat : stats)
        std::cout << stat;
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

        auto timesIt = eventsIt->second.begin();
        std::advance(timesIt, eventsIt->second.size() / 2);
        statistics.mMedian = *timesIt;
    }
    return statistics;
}


