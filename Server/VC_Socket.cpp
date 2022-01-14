#include "VC_Socket.h"

namespace vc
{
    Vc_Socket::Vc_Socket() : _sockfd(0), _Domain(AF_INET), _type(SOCK_STREAM)
    {
    }

    Vc_Socket::~Vc_Socket()
    {
        if(_sockfd >= 0)
        {
            ::close(_sockfd);
        }
    }

    bool Vc_Socket::Create_socket(int Domain, int type)
    {
        _Domain = Domain;
        _type = type;
        _sockfd = socket(_Domain, _type, 0);
        if(_sockfd == -1)
        {
            return false;
        }

        return true;
    }

    bool Vc_Socket::bind(const std::string ip, const int port)
    {
        struct sockaddr_in addr;
        bzero(&addr, sizeof(addr));

        addr.sin_family = _Domain;
        addr.sin_port = htons(port);

        if(ip == "")
        {
            addr.sin_addr.s_addr = htonl(INADDR_ANY);
        }
        else
        {
            return parseAddr(ip, addr.sin_addr);
        }

        try
        {
            bind(addr, sizeof(addr));
            return true;
        }
        catch(...)
        {
            std::cout << "catch bind error " << std::endl;
        }

        return false;
    }

    bool Vc_Socket::parseAddr(const std::string ip, struct in_addr &addr)
    {
        int ret = inet_pton(AF_INET, ip.c_str(), &addr);

        if(ret < 0)
        {
            std::cout << "pton set error" << std::endl;
        }
        else if(ret == 0)
        {
            /*
             * struct hostent {
                char *h_name;         //正式主机名
                char **h_aliases;     //主机别名
                int h_addrtype;       //主机IP地址类型：IPV4-AF_INET
                int h_length;         //主机IP地址字节长度，对于IPv4是四字节，即32位
                char **h_addr_list;   //主机的IP地址列表
                };
             */
            struct hostent stHostent;
            struct hostent *pstHostent = nullptr;
            char **pptr = nullptr;

            char buf[2048] = "\0";
            sprintf(buf,"%s", ip.c_str());
            int iError;

            if((pstHostent = gethostbyname(buf)) == NULL || pstHostent->h_addr_list == NULL || pstHostent->h_addr_list[0] == NULL)
            {
                std::cout << "can't parse the domain" << std::endl;
            }
            else
            {
//                std::cout << "official hostname: " << pstHostent->h_name << std::endl;
                for(pptr = pstHostent->h_aliases; *pptr != NULL; pptr++)
                    ;
//                    std::cout << "alias: " << *pptr << std::endl;
                switch(pstHostent->h_addrtype)
                {
                    case AF_INET:
                    case AF_INET6:
                        pptr = pstHostent->h_addr_list;
                        for(; *pptr!=NULL; pptr++)
                            ;
//                            printf("address:%s\n",inet_ntop(pstHostent->h_addrtype, *pptr, buf,64));
//                        printf("first address: %s\n",inet_ntop(pstHostent->h_addrtype, pstHostent->h_addr,buf,64));
                        addr = *(struct in_addr *)pstHostent->h_addr;
                        return true;
                        break;
                    default:
                        std::cout << "unknown address type" << std::endl;
//                        printf("Unkown address type\n");
                }

            }
        }
        else
        {
            return true;
        }

        return false;
    }

    void Vc_Socket::bind(const sockaddr_in &addr, socklen_t addrlen)
    {
        int reuse = 1;
        SetSocketOpt(SO_REUSEADDR, (const void *) &reuse, sizeof(int), SOL_SOCKET);

        if(::bind(_sockfd, (struct sockaddr *) &addr, addrlen) < 0)
        {
            std::cout << "::bind error" << std::endl;
        }
        else
        {
            ;
        }
    }

    int Vc_Socket::SetSocketOpt(int opt, const void *optval, socklen_t len, int level)
    {
        return setsockopt(_sockfd, level, opt, optval, len);
    }

} //vc