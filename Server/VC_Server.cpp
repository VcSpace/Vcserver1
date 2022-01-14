#include "VC_Server.h"

namespace vc
{
    Vc_Server::~Vc_Server() {

    }
    Vc_Server::Vc_Server(const std::string &ip, const int &port) : m_ip(ip), m_port(port)
    {

    }

    void Vc_Server::CreateSocket()
    {
        int Domain = AF_INET;
        int type = SOCK_STREAM;

        if(_Sock.Create_socket(Domain, type))
        {
            std::cout << "CreateSocket" << std::endl;
        }
        else
        {
            std::cout << "CreateSocket error" << std::endl;
            exit(0);
        }

    }

    void Vc_Server::bind()
    {
        if(_Sock.bind(m_ip, m_port))
        {
            std::cout << "bind ip, port success " << std::endl;
        }
        else
        {
            std::cout << "socket bind error" << std::endl;
            exit(0);
        }
    }


} //vc
