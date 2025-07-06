#ifndef QUAD_H
#define QUAD_H

#include "Object.h"

class Quad : public Object {
    public:
        Quad(const Point3d &q, const Vector3d &u, const Vector3d &v, shared_ptr<Material> m)
          : q(q), u(u), v(v), m(m), normal(normalize(crossProduct(u, v)))
        {
            // Compute the bounding box of all four vertices.
            auto aabb_diagonal1 = AABB(q, q+u+v);
            auto aabb_diagonal2 = AABB(q+u, q+v);
            aabb = AABB(aabb_diagonal1, aabb_diagonal2);
        }

        bool intersect(const Ray &ri, Interval t_interval, Intersection &isect) const override {
            
            double t = dotProduct((q - ri.origin()), normal) / dotProduct(ri.direction(), normal);
            Point3d p = ri.at(t);
            if (!t_interval.surrounds(t) || !inside_quad(p))
                return false;

            isect.p = p;
            isect.distance = t;
            isect.set_normal(ri, normal);
            get_tex_uv(isect.p, isect.tex_u, isect.tex_v);
            isect.m = m;

            return true;
        }

        AABB get_AABB() const override { return aabb; }
    
    private:
        Point3d q;
        Vector3d u, v;
        Vector3d normal;
        shared_ptr<Material> m;
        AABB aabb;

        bool inside_quad(const Point3d &p) {

        }

        static void get_tex_uv(const Point3d &p, double &tex_u, double &tex_v) {

        }
};

#endif