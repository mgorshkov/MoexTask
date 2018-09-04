#include "TcpDataSource.h"
#include "TsvParser.h"

TcpDataSource::TcpDataSource(IStopperPtr aStopper, int aPort)
    : mStopper(aStopper)
    , mPort(aPort)
    , mParser(mStream)
    , mThread(std::move(std::thread(ThreadProc, this)))
{
}

TcpDataSource::~TcpDataSource()
{
#ifdef DEBUG_PRINT
    std::cout << "~TcpDataSource" << std::endl;
#endif
    Stop();
}

DataPtr TcpDataSource::Produce()
{
    if (mStopper->IsStopped())
        return nullptr;

    std::unique_lock<std::mutex> lk(mStreamMutex);
    mCondition.wait(lk, [this](){return mStopper->IsStopped();});

    if (mStopper->IsStopped())
        return nullptr;

    return mParser.Produce();
}

void TcpDataSource::Stop()
{
#ifdef DEBUG_PRINT
    std::cout << "TcpDataSource::Stop" << std::endl;
#endif
    if (mThread.joinable())
        mThread.join();

#ifdef DEBUG_PRINT
    std::cout << "TcpDataSource::Stop - finished" << std::endl;
#endif
}

void TcpDataSource::Read(const char* aData, std::size_t aSize)
{
    if (mStopper->IsStopped())
        return;
    {
        std::lock_guard<std::mutex> lk(mStreamMutex);
        mStream.write(aData, aSize);
    }
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
#ifdef DEBUG_PRINT
        std::cout << "TcpDataSource::ThreadProc() finished" << std::endl;
#endif
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in TcpDataSource: " << e.what() << std::endl;
    }
    aContext->mCondition.notify_one();
}
