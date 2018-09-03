#include "TcpDataSource.h"
#include "TsvParser.h"

TcpDataSource::TcpDataSource(IStopperPtr aStopper, int aPort)
    : mStopper(aStopper)
    , mPort(aPort)
    , mParser(mStream)
    , mThread(std::move(std::thread(ThreadProc, this)))
{
}

DataPtr TcpDataSource::Produce()
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
    try
    {
#ifdef DEBUG_PRINT
        std::cout << "TcpDataSource::ThreadProc()" << std::endl;
#endif
        TcpServer server(aContext->mPort, aContext);
        server.Init();
        while (!aContext->mStopper->IsStopped())
        {
            server.Loop();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
