cmake_minimum_required(VERSION 3.16)
project(Vcserver)

set(CMAKE_CXX_STANDARD 11)

add_executable(Vcserver
        Server/VC_Server.cpp
        Server/VC_Socket.cpp
        main.cpp)
