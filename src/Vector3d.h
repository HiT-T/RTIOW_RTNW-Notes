#ifndef VECTOR3D_H
#define VECTOR3D_H

class Vector3d {
    public:
        double e[3];

        Vector3d() : e{.0,.0,.0} {}
        Vector3d(double e0, double e1, double e2) : e{e0,e1,e2} {}

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        Vector3d operator-() const { return Vector3d(-e[0],-e[1],-e[2]); }
        double operator[](int i) const { return e[i]; } // guarantees const objects(' member variables) unchanged.
        double& operator[](int i) { return e[i]; } // allows mutable objects to be changed.

        Vector3d& operator+=(const Vector3d &v) {
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];

            return *this;
        }

        Vector3d& operator-=(const Vector3d &v) {
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];

            return *this;
        }

        Vector3d& operator*=(double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;

            return *this;
        }

        Vector3d& operator/=(double t) {
            return *this *= 1/t;
        }

        double norm_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }

        double norm() const {
            return std::sqrt(norm_squared());
        }

        bool near_zero() const {
            auto s = 1e-8;
            return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) && (std::fabs(e[2]) < s); 
        }

        static Vector3d sample() { 
            return Vector3d(sample_double(), sample_double(), sample_double()); 
        }

        static Vector3d sample(double min, double max) {
             return Vector3d(sample_double(min, max), sample_double(min, max), sample_double(min, max));
        }
};

// alias makes codes more readable.
using Point3d = Vector3d;

// functions that utilize Vector3d objects.

inline std::ostream& operator<<(std::ostream &out, const Vector3d &v) {
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline Vector3d operator+(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline Vector3d operator-(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
}

inline Vector3d operator*(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

inline Vector3d operator*(double t, const Vector3d &v) {
    return Vector3d(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vector3d operator*(const Vector3d &v, double t) {
    return Vector3d(v.e[0]*t, v.e[1]*t, v.e[2]*t);
}

inline Vector3d operator/(const Vector3d &v, double t) {
    return Vector3d(v.e[0]/t, v.e[1]/t, v.e[2]/t);
}

inline double dotProduct(const Vector3d &u, const Vector3d &v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
}

inline Vector3d crossProduct(const Vector3d &u, const Vector3d &v) {
    return Vector3d(u.e[1]*v.e[2] - v.e[1]*u.e[2], 
                 u.e[2]*v.e[0] - v.e[2]*u.e[0], 
                 u.e[0]*v.e[1] - v.e[0]*u.e[1]);
}

inline Vector3d sample_in_unit_disk() {
    while (true) {
        auto p = Vector3d(sample_double(-1,1), sample_double(-1,1), 0);
        if (p.norm_squared() < 1) 
            return p;
    }
}

inline Vector3d normalize(const Vector3d &v) {
    return v / v.norm();
}

inline Vector3d sample_random_dir() {
    while (true) {
        auto p = Vector3d::sample(-1,1);
        auto p_norm = p.norm();
        if (1e-160 < p_norm && p_norm <= 1) {
            return p / p_norm;
        }
    }
}

inline Vector3d sample_outward_dir(const Vector3d &N) {
    auto random_dir = sample_random_dir();
    if (dotProduct(random_dir, N) > 0.0) {
        return random_dir;
    } else {
        return -random_dir;
    }
}

#endif