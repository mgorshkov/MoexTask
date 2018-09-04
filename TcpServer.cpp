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
    , mBindSocket(-1)
    , mSocket(-1)
    , mReader(aReader)
{
}

bool TcpServer::CreateSocket()
{
    mBindSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mBindSocket < 0)
    { 
        std::cerr << "error opening socket" << std::endl;
        return false;
    }
    return true;
}

void TcpServer::SetSockOpt()
{
    int optval = 1;
    setsockopt(mBindSocket, SOL_SOCKET, SO_REUSEADDR, 
        (const void*)&optval, sizeof(optval));

    struct timeval readTimeout;
    readTimeout.tv_sec = 1;
    readTimeout.tv_usec = 0;
    setsockopt(mBindSocket, SOL_SOCKET, SO_RCVTIMEO, &readTimeout, sizeof(readTimeout));
}

bool TcpServer::Bind()
{
    sockaddr_in serveraddr{0};
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)mPort);

    if (bind(mBindSocket, (sockaddr*)&serveraddr,  sizeof(serveraddr)) < 0) 
    {
        std::cerr << "error binding socket" << std::endl;
        return false;
    }

    return true;
}

bool TcpServer::Listen()
{
    if (listen(mBindSocket, 1) < 0)
    {
        std::cerr << "error listening socket" << std::endl;
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

    if (!Listen())
        return false;

    return true;
}

bool TcpServer::Loop()
{
#ifdef DEBUG_PRINT
    std::cout << "TCP server: Loop()" << std::endl;
#endif

    sockaddr_in clientaddr;
    socklen_t clientlen = sizeof(clientaddr);

    char buf[BufSize] = {0};
    mSocket = accept(mBindSocket, (sockaddr*)&clientaddr, &clientlen);
    if (mSocket < 0)
    {
#ifdef DEBUG_PRINT
        std::cerr << "error on accept" << std::endl;
#endif
        return false;
    }
    
    auto hostp = gethostbyaddr((const char*)&clientaddr.sin_addr.s_addr, 
        sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == nullptr)
    {
        std::cerr << "error on gethostbyaddr" << std::endl;
        return false;
    }
    auto hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == nullptr)
    {
        std::cerr << "error on inet_ntoa" << std::endl;
        return false;
    }
#ifdef DEBUG_PRINT
    std::cout << "Server established connection with " << hostp->h_name << "(" << hostaddrp << ")" << std::endl; 
#endif
    int n = read(mSocket, buf, sizeof(buf));
    if (n < 0)
    {
        std::cerr << "error in read" << std::endl;
        return false;
    }

#ifdef DEBUG_PRINT
    std::cout << "TCP server: received " << n << " bytes: " << buf << std::endl;
#endif

    mReader->Read(buf, n);

    return true;
}
