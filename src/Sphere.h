#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
    public:
        Sphere(const Point3d &center, double radius, shared_ptr<Material> m) 
            : center(center), radius(std::fmax(0,radius)), m(m) {}

        bool intersect(const Ray &ri, Interval t_interval, Intersection &isect) const override {
            Vector3d d = ri.direction(), oc = center - ri.origin();
            auto a = d.norm_squared();
            auto h = dotProduct(d, oc);
            auto c = oc.norm_squared() - radius*radius;

            auto discriminant = h*h - a*c;
            if (discriminant < 0) {
                return false; 
            } 

            auto sqrtd = std::sqrt(discriminant);
            auto t = (h - sqrtd) / a;
            if (!t_interval.surrounds(t)) {
                t = (h + sqrtd) / a;
                if (!t_interval.surrounds(t)) {
                    return false;
                }
            }

            isect.p = ri.at(t);
            isect.distance = t;
            auto outward_normal = (isect.p - center) / radius;
            isect.set_normal(ri, outward_normal);
            isect.m = m;

            return true;
        }
    private:
        Point3d center;
        double radius;
        shared_ptr<Material> m;
};

#endif