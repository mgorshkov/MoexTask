#pragma once

class UdpClient
{
public:
    UdpClient(const std::string& aHost, int aPort, const std::string& aEvent);

    bool Init();

    bool Run();

private:
    bool CreateSocket();

    static const int BufSize = 1024;

    std::string mHost;
    int mPort;
    std::string mEvent;
    int mSocket;
};
