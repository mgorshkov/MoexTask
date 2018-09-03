#include "IConsumer.h"
#include "IStatsQuery.h"
#include "Defines.h"
#include "Synchronizer.h"

class StatisticsAnalyzer : public IConsumer, public IStatsQuery
{
public:
    StatisticsAnalyzer(Synchronizer& aSynchronizer);

    void Consume(DataPtr&& aData) override;

    EventStatisticsVector EventStats() const override;
    EventStatistics EventStats(const EventName& aEvent) const override;

    TotalStatisticsVector TotalStats() const override;

private:
    Synchronizer& mSynchronizer;
    Log mEvents;
    Times mTimes;

    static int constexpr Multiplier = 5;
};
