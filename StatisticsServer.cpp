#include "StatisticsServer.h"

StatisticsServer::StatisticsServer(std::optional<std::string> aDataFileName, std::optional<std::string> aFifoFileName, std::optional<int> aTcpPort, int aUdpPort)
    : mDataFileName(aDataFileName)
    , mFifoFileName(aFifoFileName)
    , mTcpPort(aTcpPort)
    , mUdpPort(aUdpPort)
{
}

void StatisticsServer::Init()
{
    if (mDataFileName)
        mSources.emplace_back(std::make_unique<FileDataSource>(mStopper, *mDataFileName));
    if (mFifoFileName)
        mSources.emplace_back(std::make_unique<FifoDataSource>(*mFifoFileName));
    if (mTcpPort)
        mSources.emplace_back(std::make_unique<TcpDataSource>(*mDataFileName));
}

void StatisticsServer::Run()
{
    mStopper = std::make_shared<IStopper>();
    Synchronizer synchronizer(mStopper);

    Log log;
    for (const auto& source : sources)
        log += source->ReadLog();
    StatisticsParser parser(log);
    mUdpServer = make_unique<UdpServer>(mUdpPort, parser.GetStatistics());
    mUdpServer->Run();
}
