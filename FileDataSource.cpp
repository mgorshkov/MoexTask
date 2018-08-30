#include "FileDataSource.h"
#include "TsvParser.h"

FileDataSource::FileDataSource(IStopperPtr aStopper, const std::string& aFileName)
    : mStopper(aStopper)
    , mStream(aFileName)
    , mParser(mStream)
{
}

DataPtr FileDataSource::Produce() const
{
    return mParser.Produce();
}
