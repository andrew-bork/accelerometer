#include <mpu6050.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <socket.h>
#include <thread>
#include <cstdio>
#include <cstdlib>

math::vector euler_glob;

void exit(){
    if(remove("/run/test") < 0){
        perror("Couldn't cleanup /run/test");
    }
}

int t_since;
void thread() {
    
    std::atexit(exit);

    sock::socket client(sock::unix, sock::tcp);

    sock::un_connection unix_connection = client.un_connect("/run/test");
    char recv[1024];

    while(1){
        sprintf(recv, "%d %f %f %f", t_since, euler_glob.x, euler_glob.y, euler_glob.z);
        printf("%d %9.7f %9.7f %9.7f\n", t_since, euler_glob.x*RAD_TO_DEG, euler_glob.y*RAD_TO_DEG, euler_glob.z*RAD_TO_DEG);

        unix_connection.send(recv,strlen(recv));
        usleep(10000);
    }
}

int main(){

    std::thread socket_thread(thread);

    math::quarternion rotation(1,0,0,0), euler_q;
    math::vector euler_v;
    double data[6];
    data[3] = 10;
    data[4] = 0;
    data[5] = 0;
    int i = 0;
    auto then = std::chrono::steady_clock::now();
    auto start = then;
    auto now = std::chrono::steady_clock::now();
    while(1) {
        usleep(1000);
        now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration_cast<std::chrono::milliseconds> (now - then).count() * 0.001;
        t_since = std::chrono::duration_cast<std::chrono::milliseconds> (now - start).count();
        then = now;
        euler_v = math::vector(data[3]*dt*DEG_TO_RAD, data[4]*dt*DEG_TO_RAD, data[5]*dt*DEG_TO_RAD);
        euler_q = math::quarternion::fromEulerZYX(euler_v);
        rotation = rotation*euler_q;

        euler_glob = math::quarternion::toEuler(rotation);		
    }
}