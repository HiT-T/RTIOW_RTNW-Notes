#ifndef OBJECT_H
#define OBJECT_H

// this stores the intersection information between ray & objects.
class Intersection {
    public:
        Point3d p;
        Vector3d normal;
        double distance; // which is t (t>=0).
        bool happend_outside; // if ray-object intersection happens at object's outer surface.

        // this guarantees normal always points agianst the ray.
        void set_normal(const Ray& r, const Vector3d& outward_normal) {
            happend_outside = dotProduct(r.direction(), outward_normal) < 0.0 ? true : false;
            normal = happend_outside ? outward_normal : -outward_normal;
        }
};

class Object {
    // parent class defaultly define unused virtual functions, let for child classes to override.
    public:
        virtual ~Object() = default;

        // stores result both in return value (if intersect) & isect (intersect data).
        virtual bool intersect(const Ray& r, Interval t_interval, Intersection& isect) const = 0; 
};

#endif