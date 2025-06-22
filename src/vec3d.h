#ifndef VEC3D_H
#define VEC3D_H

#include <cmath>
#include <iostream>

class Vec3d {
    public:
        double e[3];

        Vec3d() : e{.0,.0,.0} {}
        Vec3d(double e0, double e1, double e2) : e{e0,e1,e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vec3d operator-() { return Vec3d(-e[0],-e[1],-e[2]); }
        double operator[](int i) const { return e[i]; } // guarantees const objects(' member variables) unchanged.
        double& operator[](int i) { return e[i]; } // allows mutable objects to be changed.

        Vec3d& operator+=(const Vec3d& v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return *this;
        }

        Vec3d& operator-=(const Vec3d& v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];

            return *this;
        }

        Vec3d& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        Vec3d& operator/=(double t) {
            return *this *= 1/t;
        }

        double norm_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double norm() const {
            return std::sqrt(norm_squared());
        }
};

// alias makes codes more readable.
using Point3d = Vec3d;

// functions that utilize Vec3d objects.

inline std::ostream& operator<<(std::ostream& out, const Vec3d& v) {
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline Vec3d operator+(const Vec3d& u, const Vec3d& v) {
    return Vec3d(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline Vec3d operator-(const Vec3d& u, const Vec3d& v) {
    return Vec3d(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

inline Vec3d operator*(const Vec3d& u, const Vec3d& v) {
    return Vec3d(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline Vec3d operator*(double t, const Vec3d& v) {
    return Vec3d(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3d operator*(const Vec3d& v, double t) {
    return Vec3d(v.e[0]*t, v.e[1]*t, v.e[2]*t);
}

inline Vec3d operator/(const Vec3d& v, double t) {
    return Vec3d(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline double dotProduct(const Vec3d& u, const Vec3d& v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline Vec3d crossProduct(const Vec3d& u, const Vec3d& v) {
    return Vec3d(u.e[1]*v.e[2] - v.e[1]*u.e[2], 
                 u.e[2]*v.e[0] - v.e[2]*u.e[0], 
                 u.e[0]*v.e[1] - v.e[0]*u.e[1]);
}

inline Vec3d normalized(const Vec3d& v) {
    return v / v.norm();
}

#endif