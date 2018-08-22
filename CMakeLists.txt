cmake_minimum_required(VERSION 3.2)
project(MoexTask VERSION 0.0.1)

add_executable(MoexTask Main.cpp Server.cpp)
add_executable(MoexTaskClient Client.cpp)
add_library(MoexTask Lib.cpp)

set_target_properties(MoexTask MoexTaskClient PROPERTIES
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
    CMAKE_CXX_STANDARD 17
    CMAKE_CXX_STANDARD_REQUIRED ON
)

set(CMAKE_CXX_FLAGS "-std=c++1z")

target_link_libraries(MoexTask
    MoexTask
)

set_target_properties(MoexTaskClient PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(MoexTaskClient
    ${Boost_LIBRARIES}
    MoexTask
)
