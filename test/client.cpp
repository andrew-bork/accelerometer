#include <socket.h>
#include <cstdio>
#include <cstring>

int main(){

    sock::socket client(sock::unix, sock::tcp);
    if(client.fd < 0){
        return -1;
    }

    sock::socket::un_connection unix_connection = client.un_connect("/run/test");
    char buf[1024];

    unix_connection.read(buf, 1024);
    printf("%s\n", buf);



}