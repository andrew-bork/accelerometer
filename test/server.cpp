#include <socket.h>
#include <cstdio>
#include <cstring>

int main(){

    sock::socket server(sock::unix, sock::tcp);
    if(server.fd < 0){
        return -1;
    }

    if(server.unixBind("/run/test") < 0){
        return -2;
    }

    if(server.listen(10) < 0){
        return -3;
    }

    sock::socket::un_connection unix_connection = server.un_accept();
    char recv[1024];
    unix_connection.read(recv, 1024);
    printf("Recieved: %s\n", recv);
    const char * msg = "Hello World!";
    unix_connection.send(msg, strlen(msg));





}