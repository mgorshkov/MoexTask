#include "IConsumer.h"
#include "Defines.h"

class StatisticsAnalyzer : public IConsumer
{
public:
    void Consume(DataPtr&& aData) override;
};
