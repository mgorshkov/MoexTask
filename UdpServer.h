#pragma once

class UdpServer
{
public:
    UdpServer(int aPort);

    bool Init();

    bool Loop();

private:
    bool CreateSocket();

    void SetSockOpt();

    bool Bind();

    static const int BufSize = 1024;
    int mPort;
    int mSocket;
};
