#ifndef MATERIAL_H
#define MATERIAL_H

#include "Object.h"

class Material {
    virtual ~Material() = default;

    virtual bool scatter(const Ray &ri, const Intersection &isect, Color color_factor, Ray &ro) const {
        return false;
    }
};

#endif