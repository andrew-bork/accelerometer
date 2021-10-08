#include <mpu6050.h>
#include <unistd.h>
#include <iostream>
#include <math.h>


int main(){
    mpu6050::init();
    mpu6050::set_accl_set(mpu6050::accl_range::g_2);
    mpu6050::set_gyro_set(mpu6050::gyro_range::deg_250);
    mpu6050::set_clk(mpu6050::clk::x_gyro);
    mpu6050::set_fsync(mpu6050::fsync::input_dis);
    mpu6050::set_dlpf_bandwidth(mpu6050::dlpf::hz_10);
    mpu6050::wake_up();

    mpu6050::set_offsets(1377, 161, -1343, -200, 138, 68);

    math::quarternion rotation, euler_q;
    math::vector euler_glob, euler_v;
    double data[6];
    int i = 0;
    while(1) {
        mpu6050::read(data);
        euler_v = math::vector(data[3]*0.001, data[4]*0.001, data[5]*0.001);
        euler_q = math::quarternion::fromEuler(euler_v);
        rotation = rotation * euler_q;
        euler_glob = math::quarternion::toEuler(rotation);

        printf("%4.8f %4.8f %4.8f\n", euler_glob.x, euler_glob.y, euler_glob.z);
		
        usleep(1000);
    }
}