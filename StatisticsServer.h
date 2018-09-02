#pragma once

#include <optional>
#include <vector>
#include <memory>

#include "ThreadedProducer.h"
#include "ThreadedConsumer.h"
#include "FileDataSource.h"
#include "TcpDataSource.h"
#include "StatisticsAnalyzer.h"
#include "UdpServer.h"
#include "Synchronizer.h"
#include "IStopper.h"

class StatisticsServer
{
public:
    StatisticsServer(std::optional<std::string> aDataFileName, std::optional<std::string> aFifoFileName, std::optional<int> tcpPort, int udpPort);

    void Init();

    void Start();
    void Loop();

private:
    static void ExternalBreak(int signal);
    static void DumpStatistics(int signal);

    std::optional<std::string> mDataFileName;
    std::optional<std::string> mFifoFileName;
    std::optional<int> mTcpPort;

    IStopperPtr mStopper;
    Synchronizer mSynchronizer;
 
    std::vector<std::unique_ptr<ThreadedActor>> mSources;
    
    ThreadedConsumer<StatisticsAnalyzer> mAnalyzer;

    UdpServer mUdpServer;

    static StatisticsServer* mThis;
};
