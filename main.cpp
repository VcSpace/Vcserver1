#include "Server/VC_Server.h"

int main(int argc, char **argv)
{
    int port = 20999;
    std::string ip = "";

    if(argc > 3)
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    std::cout << "Server Start" << std::endl;
    vc::Vc_Server server(ip, port);
    server.CreateSocket();
    server.bind();

    return 0;
}