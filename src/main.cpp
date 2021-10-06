#include <mpu6050.h>
#include <unistd.h>
#include <iostream>


int main(){
    mpu6050::init();
    mpu6050::print_debug();
    mpu6050::set_accl_set(mpu6050::accl_range::g_2);
    mpu6050::set_gyro_set(mpu6050::gyro_range::deg_1000);
    mpu6050::set_clk(mpu6050::clk::x_gyro);
    mpu6050::set_fsync(mpu6050::fsync::input_dis);
    mpu6050::set_dlpf_bandwidth(mpu6050::dlpf::hz_21);
    mpu6050::wake_up();
    mpu6050::print_debug();
    float x,y,z;
    float data[6];
    float s_data[6];
    for(int i = 0; i<6;i++) s_data[i]=0;
    int n = 1000;
    int i = n;
    while(i--){
        mpu6050::read(data);
        std::cout<< data[0] << " " << data[1] << " " << data[2] << " " << data[3] << " " << data[4] << " " << data[5] << "\n";
        for(int i = 0; i < 6; i++)s_data[i]+=data[i];
        usleep(1000);
    }

    std::cout<< "RESULTS: \n" << "Accel: " << s_data[0] / n << " " << s_data[1] / n << " " << s_data[2] / n <<"\nGyro: " << s_data[3] / n << " " << s_data[4] / n << " " << s_data[5] << "\n\n";

}