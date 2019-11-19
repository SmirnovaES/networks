cmake_minimum_required(VERSION 3.13)
project(networks)

set(CMAKE_CXX_STANDARD 14)

add_executable(networks main.cpp Station.cpp Station.h Network.cpp Network.h)

TARGET_LINK_LIBRARIES( networks
        pthread
        )
