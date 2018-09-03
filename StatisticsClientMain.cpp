#include <iostream>

#include "CommandLineParser.h"
#include "StatisticsClient.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc == 1)
        {
            std::cerr << "Statistics UDP client. Usage: StatisticsClient -udphost=<statistics UDP host> -udpport=<statistics UDP port> -event=<event name>" << std::endl;
            return 1;
        }

        CommandLineParser commandLineParser(argc, argv);

        auto udpHost = commandLineParser.GetOption("udphost");
        auto udpPort = commandLineParser.GetOption("udpport");
        auto event = commandLineParser.GetOption("event");
        
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

        if (!event)
        {
            std::cerr << "Event is not specified" << std::endl;
            return 1;
        }

        StatisticsClient client(*udpHost, std::atoi(udpPort->c_str()), *event);

        if (!client.Init())
            return 1;
        client.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
