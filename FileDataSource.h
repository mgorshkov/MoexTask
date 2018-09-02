#pragma once

#include <fstream>

#include "Defines.h"
#include "IProducer.h"
#include "IStopper.h"
#include "TsvParser.h"

class FileDataSource : public IProducer
{
public:
    FileDataSource(IStopperPtr aStopper, const std::string& aFileName);

    DataPtr Produce() override;

private:
    IStopperPtr mStopper;
    TsvParser mParser;
    std::ifstream mStream;
};
