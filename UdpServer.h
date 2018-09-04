#pragma once

#include "IStatsQuery.h"

class UdpServer
{
public:
    UdpServer(int aPort, IStatsQuery* aStatsQuery);

    UdpServer(const UdpServer&) = delete;

    UdpServer& operator = (const UdpServer&) = delete;

    bool Init();

    bool Loop();

private:
    bool CreateSocket();

    void SetSockOpt();

    bool Bind();

    static const int BufSize = 1024;
    int mPort;
    int mSocket;

    IStatsQuery* mStatsQuery;
};
