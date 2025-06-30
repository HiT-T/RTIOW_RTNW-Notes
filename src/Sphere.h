#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
    public:
        // static sphere
        Sphere(const Point3d &static_center, double radius, shared_ptr<Material> m)
          : center(static_center, Vector3d(0,0,0)), radius(std::fmax(0,radius)), m(m) 
        {
            auto rVec = Vector3d(radius, radius, radius);
            aabb = AABB(static_center - rVec, static_center + rVec);
        }

        // moving sphere
        Sphere(const Point3d &center1, const Point3d &center2, double radius,
               shared_ptr<Material> m)
          : center(center1, center2 - center1), radius(std::fmax(0,radius)), m(m) 
        {
            auto rVec = Vector3d(radius, radius, radius);
            AABB aabb1 = AABB(center1 - rVec, center1 + rVec);
            AABB aabb2 = AABB(center2 - rVec, center2 + rVec);
            aabb = AABB(aabb1, aabb2);
        }

        bool intersect(const Ray &ri, Interval t_interval, Intersection &isect) const override {
            Point3d current_center = center.at(ri.time());
            Vector3d d = ri.direction(), oc = current_center - ri.origin();
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
            auto outward_normal = (isect.p - current_center) / radius;
            isect.set_normal(ri, outward_normal);
            isect.m = m;

            return true;
        }

        AABB get_AABB() const override { return aabb; }
    
    private:
        Ray center; // allows center to move from start (t = 0) to end (t = 1).
        double radius;
        shared_ptr<Material> m;
        AABB aabb;
};

#endif