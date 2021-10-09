#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>


namespace sock{
    namespace sock_domain{
        enum sock_domain {
            unix = AF_UNIX, inet=AF_INET
        };
    };
    namespace sock_type {
        enum sock_type {
            TCP=SOCK_STREAM, UDP=SOCK_DGRAM
        };
    };
    struct socket{
        struct un_connection{
            socket * s;
            bool valid;
            sockaddr_un addr;
            int fd;
            int read(char * buffer, int len);
            int send(char * buffer, int len);
        };
        struct in_connection{
            socket * s;
            bool valid;
            sockaddr_in addr;
            int fd;
            int read(char * buffer, int len);
            int send(char * buffer, int len);
        };
        int fd;
        int addr;
        int port;
        bool opened;
        //sock_domain::sock_domain domain;

        socket(sock_domain::sock_domain domain, sock_type::sock_type type);

        int setSocketOption(int lvl, int opt, const void * optval, socklen_t optlen);
        int inBind(int addr, int port);
        int unixBind(char* path);
        int listen(int backlog);
        socket::un_connection un_accept();
        socket::in_connection in_accept();
    };
}
#endif