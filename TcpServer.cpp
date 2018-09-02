#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "TcpServer.h"

TcpServer::TcpServer(int aPort, IReaderPtr aReader)
    : mPort(aPort)
    , mSocket(-1)
    , mReader(aReader)
{
}

bool TcpServer::CreateSocket()
{
    mSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mSocket < 0)
    { 
        std::cerr << "error opening socket" << std::endl;
        return false;
    }
    return true;
}

void TcpServer::SetSockOpt()
{
    int optval = 1;
    setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, 
        (const void*)&optval, sizeof(optval));

    struct timeval readTimeout;
    readTimeout.tv_sec = 10;
    readTimeout.tv_usec = 0;
    setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, &readTimeout, sizeof(readTimeout));
}

bool TcpServer::Bind()
{
    sockaddr_in serveraddr{0};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)mPort);

    if (bind(mSocket, (sockaddr*)&serveraddr,  sizeof(serveraddr)) < 0) 
    {
        std::cerr << "error binding socket" << std::endl;
        return false;
    }

    return true;
}

bool TcpServer::Init()
{
    if (!CreateSocket())
        return false;

    SetSockOpt();

    if (!Bind())
        return false;

    return true;
}

bool TcpServer::Loop()
{
    sockaddr_in clientaddr;

    char buf[BufSize] = {0};

    socklen_t clientlen = sizeof(clientaddr);

    int n = recvfrom(mSocket, buf, sizeof(buf), 0,
        (sockaddr*)&clientaddr, &clientlen);
    if (n < 0)
    {
        std::cerr << "error in recvfrom";
        return false;
    }

    mReader->Read(buf, BufSize);

    return true;
}
