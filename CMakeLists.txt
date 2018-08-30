cmake_minimum_required(VERSION 3.2)
project(MoexTask VERSION 0.0.1)

add_executable(MoexTask
    CommandLineParser.h
    CommandLineParser.cpp
    Defines.h
    FileDataSource.h
    FileDataSource.cpp
    IConsumer.h
    IProducer.h
    IStopper.h
    Main.cpp
    StatisticsAnalyzer.h
    StatisticsAnalyzer.cpp
    StatisticsServer.cpp
    StatisticsServer.h
    Stopper.h
    Stopper.cpp
    Synchronizer.h
    Synchronizer.cpp
    TcpServer.h
    TcpServer.cpp
    ThreadedActor.h
    ThreadedActor.cpp
    ThreadedConsumer.h
    ThreadedProducer.h
    TsvParser.cpp
    TsvParser.h
    UdpServer.h
    UdpServer.cpp)

add_executable(MoexTaskClient Client.cpp)
add_library(MoexTaskLib Lib.cpp)

set_target_properties(MoexTask MoexTaskClient PROPERTIES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "-std=c++1z")

target_link_libraries(MoexTask
    MoexTaskLib
)

target_link_libraries(MoexTaskClient
    MoexTaskLib
)
