#ifndef RAY_H
#define RAY_H

#include "vec3d.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3d& origin, const Vec3d& direction) : orig(origin), dir(direction) {}

        // pass const member values defaultly, but caller can copy them into mutable ones.
        const Point3d& origin() { return orig; }
        const Vec3d& direction() { return dir; }

        Point3d at(double t) const {
            return orig + t*dir;
        }

    private:
        Point3d orig;
        Vec3d dir;
};

#endif