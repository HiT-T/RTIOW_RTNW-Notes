#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "Object.h"

#include <vector>

class Scene : public Object {
    public:
        // shared_ptr ? 1. automatically frees memory; 2. allows multiple references.
        std::vector<shared_ptr<Object>> objects;

        Scene() {}
        Scene(shared_ptr<Object> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<Object> object) { objects.push_back(object); }

        bool intersect(const Ray& r, Interval t_interval, Intersection& isect) const override {
            Intersection temp_isect;
            bool happened = false;
            double closest = t_interval.max;

            for (const auto& object : objects) {
                if (object->intersect(r, Interval(t_interval.min, closest), temp_isect)) {
                    happened = true;
                    closest = temp_isect.distance;
                    isect = temp_isect;
                }
            }

            return happened;
        }
};

#endif
