#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "Object.h"
#include "Material.h"
#include "Texture.h"

class ConstantMedium : public Object {
    public:
        ConstantMedium(shared_ptr<Object> boundary, double density, const Color &albedo) 
          : boundary(boundary), negInv_density(-1/density), 
            phase_function(make_shared<Isotropic>(albedo)) 
        {}

        ConstantMedium(shared_ptr<Object> boundary, double density, shared_ptr<Texture> tex) 
          : boundary(boundary), negInv_density(-1/density),
            phase_function(make_shared<Isotropic>(tex))
        {}

        bool intersect(const Ray& ri, Interval t_interval, Intersection& isect)
        const override {
            Intersection isect1, isect2;

            if(!boundary->intersect(ri, Interval::universe, isect1))
                return false;

            if(!boundary->intersect(ri, Interval(isect1.distance+1e-4, infinity), isect2))
                return false;

            if (isect1.distance < t_interval.min) isect1.distance = t_interval.min;
            if (isect2.distance > t_interval.max) isect2.distance = t_interval.max;

            if (isect1.distance >= isect2.distance)
                return false;

            if (isect1.distance < 0)
                isect1.distance = 0; // if ray starts inside the media, adjust t to be non-negative.

            auto distance_inside_boundary = isect2.distance - isect1.distance;
            auto scatter_distance = negInv_density * std::log(sample_double());

            if (scatter_distance > distance_inside_boundary)
                return false;
            
            isect.distance = isect1.distance + scatter_distance;
            isect.p = ri.at(isect.distance);

            isect.normal = Vector3d(1,0,0);    // these two are arbitrarily set because rays are randomly & uniformly
            isect.happend_outside = true; //  scattered in any directions for isotropic material.
            isect.m = phase_function;

            return true;
        }

        AABB get_AABB() const override { return boundary->get_AABB(); }

    private:
        shared_ptr<Object> boundary;
        double negInv_density;
        shared_ptr<Material> phase_function;
};

#endif