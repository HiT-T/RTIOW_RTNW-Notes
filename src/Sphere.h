#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
    public:
        Sphere(const Point3d& center, double radius) : center(center), radius(std::fmax(0,radius)) {}

        bool intersect(const Ray& r, double t_min, double t_max, Intersection& isect) const override {
            Vector3d d = r.direction(), oc = center - r.origin();
            auto a = d.norm_squared();
            auto h = dotProduct(d, oc);
            auto c = oc.norm_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false; 
            } 

            auto sqrtd = std::sqrt(discriminant);
            auto t = (h - sqrtd) / a;
            if (t <= t_min || t >= t_max) {
                t = (h + sqrtd) / a;
                if (t <= t_min || t >= t_max) {
                    return false;
                }
            }

            isect.p = r.at(t);
            isect.distance = t;
            auto outward_normal = (isect.p - center) / radius;
            isect.set_normal(r, outward_normal);

            return true;
        }
    private:
        Point3d center;
        double radius;
};

#endif