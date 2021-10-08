#ifndef MATH_H
#define MATH_H
namespace math{

    struct vector{
        double x,y,z;
        vector();
        vector(double x);
        vector(double x, double y);
        vector(double x, double y, double z);

        vector operator+ (const vector& r);
    };

    struct quarternion{
        double w, x, y, z;
        bool unit;

        quarternion();
        quarternion(double x, double y, double z);
        quarternion(double w, double x, double y, double z);
        quarternion(double w, double x, double y, double z, bool unit);

        quarternion operator+ (const quarternion& r);
        quarternion operator* (const quarternion& r);

        static quarternion inverse(const quarternion& n);
        static quarternion conjugate(const quarternion& n);
        static quarternion rotate(double theta, const vector& axis);
        static quarternion fromEuler(const vector& euler);
    };
    double length(const quarternion& n);
    double length(const vector& n);
}
#endif