#include "StatisticsClient.h"

StatisticsClient::StatisticsClient(const std::string& aUdpHost, int aUdpPort, const std::string& aEvent)
    : mUdpClient(aUdpHost, aUdpPort, aEvent)
{
}

bool StatisticsClient::Init()
{
    return mUdpClient.Init();
}

bool StatisticsClient::Run()
{
    return mUdpClient.Run();
}



