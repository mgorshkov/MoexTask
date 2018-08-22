#include <iostream>

#include "Server.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5)
        {
            std::cerr << "Simple statistics server. Usage: Server <data file name> <data FIFO name> <data TCP port> <statistics UDP port>" << std::endl;
            return 1;
        }

        std::string dataFileName = argv[1];
        std::string fifoFileName = argv[2];
        auto tcpPort = std::atoi(argv[3]);
        auto udpPort = std::atoi(argv[4]);

        Server server(dataFileName, fifoFileName, tcpPort, udpPort);

        server.Run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
