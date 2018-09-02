#pragma once

#include "Defines.h"
#include "IProducer.h"
#include "IStopper.h"
#include "TsvParser.h"

class FifoDataSource : public IProducer
{
public:
    FifoDataSource(IStopperPtr aStopper, const std::string& aFileName);

    DataPtr Produce() override;

private:
    IStopperPtr mStopper;
    TsvParser mParser;
    int mStream;
};
