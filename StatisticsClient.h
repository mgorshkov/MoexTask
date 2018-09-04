#pragma once

#include <string>

#include "UdpClient.h"

class StatisticsClient
{
public:
    StatisticsClient(const std::string& aUdpHost, int aUdpPort, const std::string& aEvent);

    StatisticsClient(const StatisticsClient&) = delete;
    StatisticsClient& operator = (const StatisticsClient&) = delete;

    bool Init();

    bool Run();

private:
    UdpClient mUdpClient;
};
