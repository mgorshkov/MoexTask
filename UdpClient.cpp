#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UdpClient.h"

UdpClient::UdpClient(const std::string& aHost, int aPort, const std::string& aEvent)
    : mHost(aHost)
    , mPort(aPort)
    , mEvent(aEvent)
    , mSocket(-1)
{
}

bool UdpClient::CreateSocket()
{
    mSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (mSocket < 0)
    { 
        std::cerr << "error opening socket" << std::endl;
        return false;
    }
    return true;
}

bool UdpClient::Init()
{
    if (!CreateSocket())
        return false;

    return true;
}

bool UdpClient::Run()
{
    hostent *server = gethostbyname(mHost.c_str());
    if (server == nullptr)
    {
        std::cerr << "error, no such host " << mHost << std::endl;
        return false;
    }

    sockaddr_in serveraddr = {0};
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
      (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(mPort);

    char buf[BufSize] = {0};

    strcpy(buf, mEvent.c_str());

    socklen_t serverlen = sizeof(serveraddr);

    int n = sendto(mSocket, buf, mEvent.length(), 0, (struct sockaddr*)&serveraddr, serverlen);
    if (n < 0)
    {
        std::cerr << "error on send" << std::endl;
        return false;
    }

    n = recvfrom(mSocket, buf, BufSize, 0, (sockaddr*)&serveraddr, &serverlen);
    if (n < 0)
        return false;
#ifdef DEBUG_PRINT
    std::cout << "UDP: received " << n << " bytes" << std::endl;
#endif

    std::cout << buf << std::endl;

    return true;
}
