#pragma once


class Server
{
public:
    Server(const std::string& aDataFileName, const std::string& aFifoFileName, int tcpPort, int udpPort);

    void Run();

private:
    TcpServer mTcpServer;
    UdpServer mUdpServer;
};
