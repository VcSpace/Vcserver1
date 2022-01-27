cmake_minimum_required(VERSION 3.16)
project(Vcserver)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
        Server/VC_Server.cpp
        Server/VC_Socket.cpp
        Epoll/VC_Epoller.cpp
        Timer/VC_Timer.cpp
        Thread/VC_Lock.cpp
        main.cpp)

#target_link_libraries(${PROJECT_NAME} -pthread -lmysqlclient)
target_link_libraries(${PROJECT_NAME} -pthread)
