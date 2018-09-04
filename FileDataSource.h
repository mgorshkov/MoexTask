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

    FileDataSource(const FileDataSource&) = delete;

    FileDataSource& operator = (const FileDataSource&) = delete;

    DataPtr Produce() override;

private:
    IStopperPtr mStopper;
    TsvParser mParser;
    std::ifstream mStream;
};
