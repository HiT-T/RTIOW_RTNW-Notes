#ifndef RAY_H
#define RAY_H

#include "Vector3d.h"

class Ray {
    public:
        Ray() {}
        Ray(const Point3d& origin, const Vector3d& direction) : Ray(origin, direction, 0) {}
        
        Ray(const Point3d& origin, const Vector3d& direction, double tm) : orig(origin), dir(direction), tm(tm) {}

        // pass const member values defaultly, but caller can copy them into mutable ones.
        const Point3d& origin() const { return orig; }
        const Vector3d& direction() const { return dir; }

        double time() const { return tm; }

        Point3d at(double t) const {
            return orig + t*dir;
        }

    private:
        Point3d orig;
        Vector3d dir;
        double tm; // the time of ray emitting while shutter opens.
};

#endif