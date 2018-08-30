#pragma once

#include <optional>
#include <vector>
#include <memory>

#include "ThreadedProducer.h"
#include "UdpServer.h"

class StatisticsServer
{
public:
    StatisticsServer(std::optional<std::string> aDataFileName, std::optional<std::string> aFifoFileName, std::optional<int> tcpPort, int udpPort);

    void Run();

private:
    ThreadedProducer<FileDataSource> mFileDataSource;
    StatisticsAnalyzer mAnalyzer;
    UdpServer mUdpServer;
};
