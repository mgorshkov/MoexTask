#include "TcpDataSource.h"
#include "TsvParser.h"

TcpDataSource::TcpDataSource(IStopperPtr aStopper, int aPort)
    : mStopper(aStopper)
    , mPort(aPort)
    , mParser(mStream)
{
}

DataPtr TcpDataSource::Produce() const
{
    std::lock_guard<std::mutex> lk(mStreamMutex);
    return mParser.Produce();
}

void TcpDataSource::Read(const char* aData, std::size_t aSize)
{
    if (mStopper->IsStopped())
        return;
    {
        std::lock_guard<std::mutex> lk(mStreamMutex);
        mStream.write(aData, aSize);
    }
    mNotified = true;
    mCondition.notify_one();
}

void TcpDataSource::ThreadProc(TcpDataSource* aContext)
{
    TcpServer server(aContext->mPort, aContext);
    server.Init();
    while (!aContext->mStopper->IsStopped())
    {
        server.Loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
