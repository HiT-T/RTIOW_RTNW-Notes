#ifndef BVH_H
#define BVH_H

#include "AABB.h"
#include "Object.h"

class BVHNode : public Object {
    public:
        BVHNode(std::vector<shared_ptr<Object>> objects) : BVHNode(objects, 0, objects.end()) {}

        BVHNode(std::vector<shared_ptr<Object>> &objects, size_t start, size_t end) {

        }

        bool intersect(const Ray& ri, Interval t_interval, Intersection& isect) const {
            if (!aabb.intersectP(ri, t_interval)) return;

            // isect stores the closest intersection between ray & {left, right}.
            bool hit_left = left->intersect(ri, t_interval, isect);
            bool hit_right = right->intersect(ri, Interval(t_interval.min, hit_left ? isect.t : t_interval.max), isect);

            return hit_left || hit_right;
        }

        AABB get_AABB() { return aabb; }

    private:
        shared_ptr<Object> &left;
        shared_ptr<Object> &right;
        AABB aabb;
};

#endif