#pragma once

#include <string>

class StatisticsClient
{
public:
    StatisticsClient(const std::string& aUdpHost, int aUdpPort);

    void Init();

    void Start();
    void Loop();

private:
    std::string mUdpHost;
    int mUdpPort;

};
