#ifndef MATERIAL_H
#define MATERIAL_H

#include "Object.h"

class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray &ri, const Intersection &isect, Color &attenuation, Ray &ro)
        const {
            return false;
        }
};

class Diffuse : public Material {
    public:
        Diffuse(const Color &albedo) : albedo(albedo) {}

        bool scatter(const Ray &ri, const Intersection &isect, Color &attenuation, Ray &ro)
        const override {
            auto wo = isect.normal + sample_unit_vector();
            if (wo.near_zero()) {
                wo = isect.normal;
            } else {
                wo = normalize(wo);
            }
            ro = Ray(isect.p, wo);
            attenuation = albedo;
            return true;
        }
    
    private:
        Color albedo;  // here albedo == Kd == pi * f_r
};

class Metal : public Material {
    public:
        Metal(const Color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

        bool scatter(const Ray &ri, const Intersection &isect, Color &attenuation, Ray &ro)
        const override {
            // fuzzy dir = specular reflection dir + random vector in fuzz unit sphere .
            auto wo = reflect(ri.direction(), isect.normal) + fuzz * sample_unit_vector();
            ro = Ray(isect.p, normalize(wo));
            attenuation = albedo;

            // if fuzzing produces inward ray, treat it as absorbed by returning false.
            return (dotProduct(ro.direction(), isect.normal) > 0.0);
        }

    private:
        Color albedo;

        // defines the roughness of the metal's surface (1 >= fuzz >= 0).
        // note: (fuzz == 0) means specular, (fuzz == 1) means nearly diffuse.
        double fuzz;

        inline Vector3d reflect(const Vector3d &v, const Vector3d &n) const {
            return normalize(v - 2 * dotProduct(v,n) * n);
        }
};

#endif