#include <mpu6050.h>
#include <unistd.h>
#include <iostream>


int main(){
    mpu6050::init();
    mpu6050::print_debug();
    mpu6050::set_accl_set(mpu6050::accl_range::g_2);
    mpu6050::set_gyro_set(mpu6050::gyro_range::deg_500);
    mpu6050::set_clk(mpu6050::clk::x_gyro);
    mpu6050::set_fsync(mpu6050::fsync::input_dis);
    mpu6050::set_dlpf_bandwidth(mpu6050::dlpf::hz_10);
    mpu6050::wake_up();
    mpu6050::print_debug();
    
    mpu6050::calibrate(1000);
    
    mpu6050::sleep();
}