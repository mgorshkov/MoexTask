#pragma once

#include <fstream>

#include "Defines.h"
#include "IProducer.h"
#include "IStopper.h"
#include "TsvParser.h"

class FifoDataSource : public IProducer
{
public:
    FifoDataSource(IStopperPtr aStopper, const std::string& aFileName);

    DataPtr Produce() const override;

private:
    IStopperPtr mStopper;
    TsvParser mParser;
    std::ifstream mStream;
};
