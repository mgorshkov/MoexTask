#include "IAnswerer.h"
#include "IConsumer.h"
#include "Defines.h"
#include "Synchronizer.h"

class StatisticsAnalyzer : public IConsumer, public IAnswerer
{
public:
    StatisticsAnalyzer(Synchronizer& aSynchronizer);

    void Consume(DataPtr&& aData) override;

    Statistics Answer(const std::string& aEvent) override;

private:
    Log mEvents;
};
