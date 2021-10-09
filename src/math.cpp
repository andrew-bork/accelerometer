#include <math.h>
#include <cmath>


math::quarternion::quarternion(){
    w = x = y = z = 0;
    unit = false;
}

math::quarternion::quarternion(double x, double y, double z){
    w = 0;
    this->x = x;
    this->y = y;
    this->z = z;
    unit = false;
}
math::quarternion::quarternion(double w, double x, double y, double z){
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
    unit = false;
}

math::quarternion::quarternion(double w, double x, double y, double z, bool unit){
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
    this->unit = unit;
}



math::quarternion math::quarternion::operator*(const math::quarternion& r){
    quarternion res;
    res.w = w*r.w - x*r.x - y*r.y - z*r.z;
    res.x = w*r.x + x*r.w + y*r.z - z*r.y;
    res.y = w*r.y - x*r.z + y*r.w + z*r.x;
    res.z = w*r.z + x*r.x - y*r.x + z*r.w;
    return res;
}

math::quarternion math::quarternion::operator+(const math::quarternion& r){
    quarternion res;
    res.w = w*r.w - x*r.x - y*r.y - z*r.z;
    res.x = w*r.x + x*r.w + y*r.z - z*r.y;
    res.y = w*r.y - x*r.z + y*r.w + z*r.x;
    res.z = w*r.z + x*r.x - y*r.x + z*r.w;
    return res;
    
}

math::quarternion math::quarternion::conjugate(const math::quarternion& q){
    quarternion res;
    res.w = q.w;
    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;
    return res;
    
}

double math::length(const math::quarternion& q){
    return sqrt(q.w*q.w+q.x*q.x+q.y*q.y+q.z*q.z);
}

double math::length(const math::vector& v){
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}

math::quarternion math::quarternion::inverse(const math::quarternion& q){
    double len;
    if(q.unit) len = 1;
    else len = length(q);
    quarternion res;
    res.w = q.w;
    res.x = -q.x;
    res.y = -q.y;
    res.z = -q.z;
    return res;
}
math::quarternion math::quarternion::rotate(double theta, const math::vector& axis){
    quarternion res;
    res.w = cos(theta/2);
    res.x = axis.x*sin(theta/2);
    res.y = axis.y*sin(theta/2);
    res.z = axis.z*sin(theta/2);
    return res;
}

math::quarternion math::quarternion::fromEuler(const math::vector& euler){
    double theta = length(euler);
    quarternion res;
    res.w = cos(theta/2);
    res.x = euler.x*sin(theta/2)/theta;
    res.y = euler.y*sin(theta/2)/theta;
    res.z = euler.z*sin(theta/2)/theta;
    return res;
}

math::vector math::quarternion::toEuler(const math::quarternion& q){
    double  sin_p = 2*(q.w*q.y - q.z*q.x);
    if(sin_p >=1){
    vector res(0, 1.570796326794897, -2*atan2(q.x, q.w));
    }else if(sin_p <= -1){
    vector res(0, -1.570796326794897, -2 *atan2(q.x, q.w));
    }
    //asin(2*(q.w*q.y - q.z*q.x));
    vector res(atan2(2*(q.w*q.x+q.y*q.z), 1 - 2* (q.x*q.x + q.y*q.y)), asin(sin_p), atan2(2*(q.w*q.z+q.x*q.y), 1 - 2 * (q.y*q.y+q.z*q.z)));
    return res;
}

math::vector::vector (){
    x = y = z = 0;
}
math::vector::vector (double xa){
    x = xa;
    y = z = 0;
}
math::vector::vector (double xa, double ya){
    x = xa;
    y = ya;
    z = 0;
}
math::vector::vector (double xa, double ya, double za){
    x = xa;
    y = ya;
    z = za;
}

math::vector math::vector::operator+ (const math::vector& r){
    vector res(x+r.x,y+r.y,z+r.z);
    return res;
}

math::vector math::vector::operator*(const double& s){
    vector res(x*s, y*s, z*s);
    return res;
}