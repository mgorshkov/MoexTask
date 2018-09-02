#include "IConsumer.h"
#include "IStatsQuery.h"
#include "Defines.h"
#include "Synchronizer.h"

class StatisticsAnalyzer : public IConsumer, public IStatsQuery
{
public:
    StatisticsAnalyzer(Synchronizer& aSynchronizer);

    void Consume(DataPtr&& aData) override;

    void DumpStatistics();

    std::vector<Statistics> AllStats() const override;
    Statistics StatsByEvent(const EventName& aEvent) const override;

private:
    Synchronizer& mSynchronizer;
    Log mEvents;
};
