#include "FifoDataSource.h"
#include "TsvParser.h"

FifoDataSource::FifoDataSource(IStopperPtr aStopper, const std::string& aFileName)
    : mStopper(aStopper)
    , mStream(aFileName)
    , mParser(mStream)
{
}

DataPtr FifoDataSource::Produce() const
{
    return mStopper->IsStopped() ? nullptr : mParser.Produce();
}
