#ifndef AABB_H
#define AABB_H

class AABB {
    public:
        Interval x, y, z;

        AABB() {}
        AABB(const Interval &x, const Interval &y, const Interval &z) : x(x), y(y), z(z) {}

        // given two extremas, construct the AABB.
        AABB(const Point3d &p1, const Point3d &p2) {
            x = (p1[0] < p2[0]) ? Interval(p1[0], p2[0]) : Interval(p2[0], p1[0]);
            y = (p1[1] < p2[1]) ? Interval(p1[1], p2[1]) : Interval(p2[1], p1[1]);
            z = (p1[2] < p2[2]) ? Interval(p1[2], p2[2]) : Interval(p2[2], p1[2]);
        }

        // construct the union of two AABBs.
        AABB(const AABB &aabb1, const AABB &aabb2) {
            x = Interval(aabb1.x, aabb2.x);
            y = Interval(aabb1.y, aabb2.y);
            z = Interval(aabb1.z, aabb2.z);
        }

        const Interval& axis_interval(int i) const {
            if (i == 0) return x;
            if (i == 1) return y;
            return z;
        }

        bool intersectP(const Ray &ri, Interval t_interval) {
            const Point3d &ray_orig = ri.origin();
            const Vector3d ray_dir = ri.direction();
            const Vector3d invDir = Vector3d(1/ray_dir[0], 1/ray_dir[1], 1/ray_dir[2]);
            
            for (int i = 0; i < 3; i++) {
                const Interval &axis = axis_interval(i);

                double t0 = (axis.min - ray_orig[i]) * invDir[i];
                double t1 = (axis.max - ray_orig[i]) * invDir[i];

                if (t0 < t1) {
                    if (t0 > t_interval.min) t_interval.min = t0;
                    if (t1 < t_interval.max) t_interval.max = t1;
                } else {
                    if (t1 > t_interval.min) t_interval.min = t1;
                    if (t0 < t_interval.max) t_interval.max = t0;
                }

                if (t_interval.min >= t_interval.max) return false;
            }
            return true;
        }
};

#endif