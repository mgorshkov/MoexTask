#include "FifoDataSource.h"
#include "TsvParser.h"

FifoDataSource::FifoDataSource(IStopperPtr aStopper, const std::string& aFileName)
    : mStopper(aStopper)
    , mStream(0)
    , mParser(mStream)
{
    mFifo = open(aFileName.c_str(), O_RDONLY);
}

DataPtr FifoDataSource::Produce()
{
    char arr[80];
    read(mFifo, arr, sizeof(arr));
    return mStopper->IsStopped() ? nullptr : mParser.Produce();
}
