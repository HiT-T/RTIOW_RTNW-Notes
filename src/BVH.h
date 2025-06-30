#ifndef BVH_H
#define BVH_H

#include "AABB.h"
#include "Object.h"
#include "Scene.h"

#include <algorithm>

class BVHNode : public Object {
    public:
        BVHNode(std::vector<shared_ptr<Object>> objects) : BVHNode(objects, 0, objects.size()) {}

        BVHNode(std::vector<shared_ptr<Object>> &objects, size_t start, size_t end) {
            int axis = sample_int(0, 2);

            auto comparator = (axis == 0) ? compare_AABB_x
                            : (axis == 1) ? compare_AABB_y
                                          : compare_AABB_z;

            size_t object_span = end - start;

            if (object_span == 1) {
                left = right = objects[start];
            } else if (object_span == 2) {
                left = objects[start];
                right = objects[start];
            } else {
                std::sort(std::begin(objects) + start, std::begin(objects) + end, comparator);

                auto middle = start + object_span/2;
                left = BVHNode(objects, start, middle);
                right = BVHNode(objects, middle, end);
            }

            aabb = AABB(left->get_AABB(), right->get_AABB());
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

        static bool compare_AABB_pos(const shared_ptr<Object> &a, const shared_ptr<Object> &b,
                                     int axis_index) 
        {
            auto a_axis_interval = a->get_AABB().axis_interval(axis_index);
            auto b_axis_interval = b->get_AABB().axis_interval(axis_index);
            return a_axis_interval.min < b_axis_interval.min;
        }

        static bool compare_AABB_x(const shared_ptr<Object> &a, const shared_ptr<Object> &b) {
            return compare_AABB_pos(a, b, 0);
        }

        static bool compare_AABB_y(const shared_ptr<Object> &a, const shared_ptr<Object> &b) {
            return compare_AABB_pos(a, b, 1);
        }

        static bool compare_AABB_z(const shared_ptr<Object> &a, const shared_ptr<Object> &b) {
            return compare_AABB_pos(a, b, 2);
        }
};

#endif