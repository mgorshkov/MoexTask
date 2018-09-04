#pragma once

#include "IReader.h"

class TcpServer
{
public:
    TcpServer(int aPort, IReaderPtr aReader);

    TcpServer(const TcpServer&) = delete;

    TcpServer& operator = (const TcpServer&) = delete;

    bool Init();

    bool Loop();

private:
    bool CreateSocket();

    void SetSockOpt();

    bool Bind();
    bool Listen();

    static const int BufSize = 1024;
    int mPort;
    IReader* mReader;
    int mBindSocket;
    int mSocket;
};
