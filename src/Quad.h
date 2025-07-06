#ifndef QUAD_H
#define QUAD_H

#include "Object.h"

class Quad : public Object {
    public:
        Quad(const Point3d &Q, const Vector3d &u, const Vector3d &v, shared_ptr<Material> m)
          : Q(Q), u(u), v(v), m(m)
        {
            Vector3d n = crossProduct(u, v);
            normal = normalize(n);
            D = dotProduct(Q, normal);
            w = n / dotProduct(n, n);

            set_AABB();
        }

        bool intersect(const Ray &ri, Interval t_interval, Intersection &isect) const override {

            double denom = dotProduct(ri.direction(), normal);
            if (std::fabs(denom) < 1e-8) 
                return false; 
            
            double t = (D - dotProduct(ri.origin(), normal)) / denom;
            Point3d P = ri.at(t);
            Vector3d p = P - Q;
            double alpha = dotProduct(w, crossProduct(p, v));
            double beta = dotProduct(w, crossProduct(u, p));
            if (!t_interval.contains(t) || !inside_quad(alpha, beta))
                return false;

            isect.p = P;
            isect.distance = t;
            isect.set_normal(ri, normal);
            isect.tex_u = alpha;
            isect.tex_v = beta;
            isect.m = m;

            return true;
        }

        void set_AABB() {
            // Compute the bounding box of all four vertices.
            auto aabb_diagonal1 = AABB(Q, Q+u+v);
            auto aabb_diagonal2 = AABB(Q+u, Q+v);
            aabb = AABB(aabb_diagonal1, aabb_diagonal2);
        }

        AABB get_AABB() const override { return aabb; }
    
    private:
        Point3d Q; // quad's left-bottom vertice.
        Vector3d u, v; // two edge vectors from Q.
        Vector3d w;
        shared_ptr<Material> m;
        AABB aabb;
        Vector3d normal; // quad's normal.
        double D; // the D for quad's implicit fomula: ax + by + cz = D.

        bool inside_quad(double alpha, double beta) const {
            Interval unit_interval = Interval(0, 1);
            if (!unit_interval.contains(alpha) || !unit_interval.contains(beta))
                return false;

            return true;
        }
};

#endif