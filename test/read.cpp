#include <mpu6050.h>
#include <unistd.h>
#include <iostream>
#include <math.h>
#include <chrono>


int main(){
    mpu6050::init();
    mpu6050::set_accl_set(mpu6050::accl_range::g_2);
    mpu6050::set_gyro_set(mpu6050::gyro_range::deg_250);
    mpu6050::set_clk(mpu6050::clk::x_gyro);
    mpu6050::set_fsync(mpu6050::fsync::input_dis);
    mpu6050::set_dlpf_bandwidth(mpu6050::dlpf::hz_184);
    mpu6050::wake_up();

    mpu6050::set_offsets(1377, 161, -1343, -200, 138, 68);

    math::quarternion rotation(1,0,0,0), euler_q;
    math::vector euler_glob, euler_v;
    double data[6];
    int i = 0;
    auto then = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();;
    while(1) {
        usleep(100);
        now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration_cast<std::chrono::milliseconds>(now - then).count() * 0.001;
        then = now;
        mpu6050::read(data);
        euler_v = math::vector(data[3]*dt*DEG_TO_RAD, data[4]*dt*DEG_TO_RAD, data[5]*dt*DEG_TO_RAD);
        euler_q = math::quarternion::fromEuler(euler_v);
        rotation = rotation * euler_q;

        euler_glob = math::quarternion::toEuler(math::quarternion::conjugate(rotation));
        printf("%5.4f %12.8f %12.8f %12.8f %12.8f %12.8f %12.8f\n",dt, euler_v.x*RAD_TO_DEG,euler_v.y*RAD_TO_DEG, euler_v.z*RAD_TO_DEG, euler_glob.x*RAD_TO_DEG, euler_glob.y*RAD_TO_DEG, euler_glob.z*RAD_TO_DEG);
		
    }
}