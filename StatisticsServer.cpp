#include <signal.h>

#include "StatisticsServer.h"
#include "Stopper.h"

StatisticsServer* StatisticsServer::mThis = 0;

StatisticsServer::StatisticsServer(
    std::optional<std::string> aDataFileName,
    std::optional<std::string> aFifoFileName,
    std::optional<int> aTcpPort,
    int aUdpPort)
    : mDataFileName(aDataFileName)
    , mFifoFileName(aFifoFileName)
    , mTcpPort(aTcpPort)
    , mUdpServer(aUdpPort)
    , mStopper(std::make_shared<Stopper>())
    , mSynchronizer(mStopper)
    , mAnalyzer(mSynchronizer)
{
    mUdpServer.Init();
    mThis = this;
}

void StatisticsServer::Init()
{
    if (mDataFileName)
        mSources.emplace_back(std::make_unique<ThreadedProducer<FileDataSource>>(mSynchronizer, *mDataFileName));
    if (mFifoFileName)
        mSources.emplace_back(std::make_unique<ThreadedProducer<FifoDataSource>>(mSynchronizer, *mFifoFileName));
    if (mTcpPort)
        mSources.emplace_back(std::make_unique<ThreadedProducer<TcpDataSource>>(mSynchronizer, *mTcpPort));
}

void StatisticsServer::Start()
{
    for (const auto& source : mSources)
        source->Start();

    mAnalyzer.Start();
}

void StatisticsServer::Loop()
{
    signal(SIGINT, &StatisticsServer::ExternalBreak);
    signal(SIGSTOP, &StatisticsServer::ExternalBreak);
    signal(SIGUSR1, &StatisticsServer::DumpStatistics);

    while (!mSynchronizer.IsStopped())
    {
        mUdpServer.Loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    for (const auto& source : mSources)
        source->Join();

    mAnalyzer.Join();
}

void StatisticsServer::ExternalBreak(int)
{
#ifdef DEBUG_PRINT
    std::cout << "StatisticsServer::ExternalBreak" << std::endl;
#endif

    mThis->mSynchronizer.Stop();
}

void StatisticsServer::DumpStatistics(int)
{
    mThis->mAnalyzer.DumpStatistics();
}
