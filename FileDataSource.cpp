#include "FileDataSource.h"
#include "TsvParser.h"

FileDataSource::FileDataSource(IStopperPtr aStopper, const std::string& aFileName)
    : mStopper(aStopper)
    , mStream(aFileName)
    , mParser(mStream)
{
}

DataPtr FileDataSource::Produce()
{
    return mStopper->IsStopped() ? nullptr : mParser.Produce();
}
