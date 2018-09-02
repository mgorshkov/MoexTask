#include <iostream>

#include "CommandLineParser.h"
#include "StatisticsClient.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc == 1)
        {
            std::cerr << "Statistics UDP client. Usage: StatisticsClient -udphost=<statistics UDP host> -udpport=<statistics UDP port>" << std::endl;
            return 1;
        }

        CommandLineParser commandLineParser(argc, argv);

        auto udpHost = commandLineParser.GetOption("udphost");
        auto udpPort = commandLineParser.GetOption("udpport");
        
        if (!udpHost)
        {
            std::cerr << "No UDP host specified" << std::endl;
            return 1;
        }
        
        if (!udpPort)
        {
            std::cerr << "UDP port is not specified" << std::endl;
            return 1;
        }

        StatisticsClient client(*udpHost, std::atoi(udpPort->c_str()));

        client.Init();
        client.Start();
        client.Loop();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
