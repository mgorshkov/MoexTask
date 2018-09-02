cmake_minimum_required(VERSION 3.2)
project(MoexTask VERSION 0.0.1)

set(DEBUG_PRINT "1")

if (DEBUG_PRINT)
    message("DEBUG_PRINT is activated!")
    add_definitions(-DDEBUG_PRINT)
endif()

add_executable(StatisticsServer
    Defines.h
    FileDataSource.h
    FileDataSource.cpp
    IConsumer.h
    IProducer.h
    IReader.h
    IStatsQuery.h
    IStopper.h
    StatisticsServerMain.cpp
    StatisticsAnalyzer.h
    StatisticsAnalyzer.cpp
    StatisticsServer.cpp
    StatisticsServer.h
    Stopper.h
    Stopper.cpp
    Synchronizer.h
    Synchronizer.cpp
    TcpDataSource.h
    TcpDataSource.cpp
    TcpServer.h
    TcpServer.cpp
    ThreadedActor.h
    ThreadedActor.cpp
    ThreadedConsumer.h
    ThreadedProducer.h
    TsvParser.cpp
    TsvParser.h
    UdpServer.h
    UdpServer.cpp
)

add_executable(StatisticsClient
    StatisticsClientMain.cpp
    StatisticsClient.cpp)

add_library(StatisticsLib
    CommandLineParser.h
    CommandLineParser.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(StatisticsServer Threads::Threads)

set_target_properties(StatisticsServer StatisticsClient PROPERTIES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "-std=c++1z")

target_link_libraries(StatisticsServer
    StatisticsLib
)

target_link_libraries(StatisticsClient
    StatisticsLib
)
