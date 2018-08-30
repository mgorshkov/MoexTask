#include "FileDataSource.h"

FileDataSource::FileDataSource(IStopperPtr aStopper, const std::string& aFileName)
    : mStopper(aStopper)
    , mStream(aFileName)
{
}

DataPtr FileDataSource::Produce()
{
    TsvParser parser(mStream);
    return parser.GetLog();
}
