#ifndef OBJECT_H
#define OBJECT_H

#include "AABB.h"

class Material; // pre-defining solves circularity of references between Object & Material classes.

// this stores the intersection information between ray & objects.
class Intersection {
    public:
        Point3d p;
        Vector3d normal;
        shared_ptr<Material> m; // material of hitted object.
        double tex_u, tex_v; // texture (u,v) coordinate of hitted object at p.
        double distance; // which is t (t>=0).
        bool happend_outside; // if ray-object intersection happens at object's outer surface.

        // this guarantees normal always points agianst the ray.
        void set_normal(const Ray &ri, const Vector3d &outward_normal) {
            happend_outside = dotProduct(ri.direction(), outward_normal) < 0.0 ? true : false;
            normal = happend_outside ? outward_normal : -outward_normal;
        }
};

class Object {
    // parent class defaultly define unused virtual functions, let for child classes to override.
    public:
        virtual ~Object() = default;

        // stores result both in return value (if intersect) & isect (intersect data).
        virtual bool intersect(const Ray& ri, Interval t_interval, Intersection& isect) const = 0; 

        virtual AABB get_AABB() const = 0;
};

class Translate : public Object {
    public:
        Translate(shared_ptr<Object> obj, Vector3d offset)
          : obj(obj), offset(offset) 
        {
            aabb = obj->get_AABB() + offset;
        }

        bool intersect(const Ray& ri, Interval t_interval, Intersection& isect) {
            Ray offset_ri(ri.origin() - offset, ri.direction(), ri.time());

            if(!obj->intersect(offset_ri, t_interval, isect))
                return false;
            
            isect.p += offset;

            return true;
        }

        AABB get_AABB() { return aabb; }

    private:
        shared_ptr<Object> obj;
        Vector3d offset;
        AABB aabb;
};

#endif