#include <socket.h>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <sys/un.h>

inline int _socket(int d, int t, int p){
    return socket(d, t, p);
}

sock::socket::socket(sock_domain::sock_domain domain, sock_type::sock_type type){
    fd = _socket((int) domain, (int) type, 0);
    opened = false;
    addr = 0;
    port = 0;
}



inline int _bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    return bind(sockfd, addr, addrlen);
}

inline int _listen(int sockfd, int back){
    return listen(sockfd, back);
}

inline int _accept(int fd, sockaddr *addr, socklen_t *addrlen){
    return accept(fd, addr, addrlen);
}


int sock::socket::setSocketOption(int lvl, int opt, const void * optval, socklen_t optlen){
    return setsockopt(fd,lvl, opt, &optval, sizeof(optval));
}

int sock::socket::inBind(int addr, int port){
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = addr;
    address.sin_port = htons(port);
    int len = sizeof(address);
    int e = bind(fd, (sockaddr *) &address, len);
    if(e<0){
        printf("Failed to bind.\n");
    }
    return e;
}

int sock::socket::unixBind(char* path){
    sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, path);
    int len = sizeof(address);
    int e = bind(fd, (sockaddr *) &address, len);
    if(e<0){
        printf("Failed to bind.\n");
    }
    return e;
}

int sock::socket::listen(int backlog){
    int e = _listen(fd, backlog);
    if(e<0){
        printf("Failed to listen.\n");
    }
    return e;
}

sock::socket::connection sock::socket::un_accept(){
    un_connection c;
    c.s = this;
    int len = sizeof(c.addr);
    c.fd = _accept(fd, &c.addr, (socklen_t *) &len);
    c.valid = c.fd<0;
    if(!c.valid){
        printf("Failed to accept.\n");
    }
    return c;
}

sock::socket::connection sock::socket::in_accept(){
    in_connection c;
    c.s = this;
    int len = sizeof(c.addr);
    c.fd = _accept(fd, &c.addr, (socklen_t *) &len);
    c.valid = c.fd<0;
    if(!c.valid){
        printf("Failed to accept.\n");
    }
    return c;
}