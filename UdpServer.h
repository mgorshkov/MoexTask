#pragma once

class UdpServer
{
public:
    UdpServer();

private:
    static const int BufSize = 1024;
    int mSocket;
};
