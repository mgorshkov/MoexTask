#include <iostream>

#include "Server.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc == 1)
        {
            std::cerr << "Simple statistics server. Usage: StatisticsServer -filename=<data file name> -fifoname=<data FIFO name> -tcpport=<data TCP port> -udpport=<statistics UDP port>" << std::endl;
            return 1;
        }

        CommandLineParser commandLineParser(argc, argv);

        auto dataFileName = commandLineParser.GetOption("filename");
        auto fifoFileName = commandLineParser.GetOption("fifoname");
        auto tcpPort = commandLineParser.GetOption("tcpport");
        auto udpPort = commandLineParser.GetOption("udpport");
        
        if (!dataFileName && !fifoFileName && !tcpPort)
        {
            std::cerr << "No data sources specified" << std::endl;
            return 1;
        }
        
        if (!udpPort)
        {
            std::cerr << "UDP port is not specified" << std::endl;
            return 1;
        }

        Server server(dataFileName, fifoFileName, tcpPort, udpPort);

        server.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
