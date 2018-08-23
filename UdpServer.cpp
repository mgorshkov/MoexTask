#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "UdpServer.h"

UdpServer::UdpServer(int aPort)
    : mPort(aPort)
{
}

void Run()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    { 
        std::cerr << "error opening socket" << std::ednl;
        return;
    }

    int optval = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, 
        (const void*)&optval, sizeof(optval));

    sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons((unsigned short)mPort);

    if (bind(sockfd, (sockaddr*)&serveraddr,  sizeof(serveraddr)) < 0) 
    {
        std::cerr << "error binding socket" << std::endl;
        return;
    }

    sockaddr_in clientaddr;

    char buf[BufSize];

    int clientlen = sizeof(clientaddr);
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        int n = recvfrom(sockfd, buf, sizeof(buf), 0,
            (sockaddr*)&clientaddr, &clientlen);
        if (n < 0)
        {
            std::cerr << "error in recvfrom";
            return;
        }

        hostent *hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, 
              sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == nullptr)
        {
            std::cerr << "error on gethostbyaddr";
            return;
        }
        char *hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == nullptr)
        {
            std::cerr << "error on inet_ntoa" << std::endl << "datagram from " << hostp->h_name << "(" << hostaddrp << ")" << std::endl, 
            std::cerr << "received %d/%d bytes: %s\n", strlen(buf), n, buf);
            return;
        }   
        n = sendto(sockfd, buf, strlen(buf), 0, 
           (struct sockaddr *) &clientaddr, clientlen);
        if (n < 0)
        {
            std::cerr << "error on response";
            return;
        }
    }
}
