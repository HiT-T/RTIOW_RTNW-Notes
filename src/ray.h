#ifndef RAY_H
#define RAY_H

#include "Vector3d.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3d& origin, const Vector3d& direction) : orig(origin), dir(direction) {}

        // pass const member values defaultly, but caller can copy them into mutable ones.
        const Point3d& origin() const { return orig; }
        const Vector3d& direction() const { return dir; }

        Point3d at(double t) const {
            return orig + t*dir;
        }

    private:
        Point3d orig;
        Vector3d dir;
};

#endif