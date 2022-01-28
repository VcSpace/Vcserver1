#include "Server/VC_Server.h"

int main(int argc, char **argv)
{
    int port = 20999;
    std::string ip = "";
    int epollevent = 1024;
    int maxconn = 128;

    if(argc > 3)
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    std::cout << "Server Start" << std::endl;
    vc::VC_Server *server = new vc::VC_Server(ip, port, epollevent, maxconn, true, 8, 1024);
    server->CreateSocket();
    server->CreateEpoll();
    server->CreateThread();
    server->run();

    return 0;
}