#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H

#include "Object.h"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class ObjectList : public Object {
    public:
        // shared_ptr ? 1. automatically frees memory; 2. allows multiple references.
        std::vector<shared_ptr<Object>> objects;

        ObjectList() {}
        ObjectList(shared_ptr<Object> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<Object> object) { objects.push_back(object); }

        bool intersect(const Ray& r, double t_min, double t_max, Intersection& isect) const override {
            Intersection temp_isect;
            bool happened = false;
            double closest = t_max;

            for (const auto& object : objects) {
                if (object->intersect(r, t_min, closest, temp_isect)) {
                    happened = true;
                    closest = temp_isect.distance;
                    isect = temp_isect;
                }
            }

            return happened;
        }
};

#endif
