#pragma once

#include <optional>
#include <vector>
#include <memory>

#include "ThreadedProducer.h"
#include "FileDataSource.h"
#include "StatisticsAnalyzer.h"
#include "UdpServer.h"
#include "Synchronizer.h"
#include "IStopper.h"

class StatisticsServer
{
public:
    StatisticsServer(std::optional<std::string> aDataFileName, std::optional<std::string> aFifoFileName, std::optional<int> tcpPort, int udpPort);

    void Run();

private:
    std::optional<std::string> mDataFileName;
    std::optional<std::string> mFifoFileName;
    std::optional<int> mTcpPort;
    int mUdpPort;

    IStopperPtr mStopper;
 
    ThreadedProducer<FileDataSource> mFileDataSource;
    ThreadedProducer<FifoDataSource> mFifoDataSource;
    ThreadedProducer<TcpDataSource> mTcpDataSource;
    
    ThreadedConsumer<StatisticsAnalyzer> mAnalyzer;

    UdpServer mUdpServer;
};
