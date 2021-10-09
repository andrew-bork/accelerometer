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
    const char * msg = "Hello World!\n";
    unix_connection.send(msg, strlen(msg));





}