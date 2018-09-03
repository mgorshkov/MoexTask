#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

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
    , mStopper(std::make_shared<Stopper>())
    , mSynchronizer(mStopper)
    , mAnalyzer(mSynchronizer)
    , mUdpServer(aUdpPort, mAnalyzer.GetConsumer())
{
    mUdpServer.Init();
    mThis = this;
}

bool StatisticsServer::Init()
{
    mSources.clear();
    if (mDataFileName)
    {
        if (access(mDataFileName->c_str(), F_OK) == -1)
        {
            std::cerr << "File " << *mDataFileName << " doest not exist." << std::endl;
            return false;
        }
        mSources.emplace_back(std::make_unique<ThreadedProducer<FileDataSource>>(mSynchronizer, *mDataFileName));
    }
    if (mFifoFileName)
        mSources.emplace_back(std::make_unique<ThreadedProducer<FileDataSource>>(mSynchronizer, *mFifoFileName));
    if (mTcpPort)
        mSources.emplace_back(std::make_unique<ThreadedProducer<TcpDataSource>>(mSynchronizer, *mTcpPort));

    return true;
}

void StatisticsServer::Start()
{
    for (const auto& source : mSources)
        source->Start();

    mAnalyzer.Start();
}

void StatisticsServer::Loop()
{
#ifdef DEBUG_PRINT
    std::cout << "StatisticsServer::Loop" << std::endl;
#endif

    signal(SIGINT, &StatisticsServer::ExternalBreak);
    signal(SIGSTOP, &StatisticsServer::ExternalBreak);
    signal(SIGUSR1, &StatisticsServer::DumpStatistics);

    while (!mSynchronizer.IsStopped())
    {
        mUdpServer.Loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

#ifdef DEBUG_PRINT
    std::cout << "StatisticsServer::Loop, before Join" << std::endl;
#endif

    for (const auto& source : mSources)
        source->Join();

    mAnalyzer.Join();

#ifdef DEBUG_PRINT
    std::cout << "StatisticsServer::Loop, finished" << std::endl;
#endif
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
#ifdef DEBUG_PRINT
    std::cout << "StatisticsServer::DumpStatistics" << std::endl;
#endif

    auto consumer = mThis->mAnalyzer.GetConsumer();

    auto eventStats = consumer->EventStats();
    std::cout << eventStats;

    auto totalStats = consumer->TotalStats();
    std::cout << totalStats;
}
