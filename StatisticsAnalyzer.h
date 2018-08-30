#include "IConsumer.h"

class StatisticsAnalyzer : public IConsumer
{
public:
    virtual void Consume(DataPtr&& aData) = 0;


};
