#include <socket.h>
#include <cstdio>
#include <cstring>

int main(){

    sock::socket client(sock::unix, sock::tcp);
    if(client.fd < 0){
        return -1;
    }

    sock::un_connection unix_connection = client.un_connect("/run/test");
    char *msg = "SUCCESS";
    unix_connection.send(msg, strlen(msg));
    char buf[1024];
    unix_connection.read(buf, 1024);
    printf("%s\n", buf);



}