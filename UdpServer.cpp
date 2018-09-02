#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UdpServer.h"

UdpServer::UdpServer(int aPort)
    : mPort(aPort)
    , mSocket(-1)
{
}

bool UdpServer::CreateSocket()
{
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket < 0)
    { 
        std::cerr << "error opening socket" << std::endl;
        return false;
    }
    return true;
}

void UdpServer::SetSockOpt()
{
    int optval = 1;
    setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, 
        (const void*)&optval, sizeof(optval));

    struct timeval readTimeout;
    readTimeout.tv_sec = 0;
    readTimeout.tv_usec = 0;
    setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, &readTimeout, sizeof(readTimeout));
}

bool UdpServer::Bind()
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

bool UdpServer::Init()
{
    if (!CreateSocket())
        return false;

    SetSockOpt();

    if (!Bind())
        return false;

    return true;
}

bool UdpServer::Loop()
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

    hostent *hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
          sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == nullptr)
    {
        std::cerr << "error on gethostbyaddr";
        return false;
    }
    char *hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == nullptr)
    {
        std::cerr << "error on inet_ntoa" << std::endl << "datagram from " << hostp->h_name << "(" << hostaddrp << ")" << std::endl, 
        std::cerr << "received " << strlen(buf) << "/" << n << " bytes: " << buf << std::endl;
        return false;
    }   
    n = sendto(mSocket, buf, strlen(buf), 0, 
       (struct sockaddr *) &clientaddr, clientlen);
    if (n < 0)
    {
        std::cerr << "error on response";
        return false;
    }

    return true;
}
