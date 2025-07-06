#ifndef PERLIN_H
#define PERLIN_H

class Perlin {
    public:
        Perlin() {
            for (int i = 0; i < point_count; i++) {
                random_vector[i] = normalize(Vector3d::sample(-1,1));
            }
            
            perlin_generate_perm(perm_x);
            perlin_generate_perm(perm_y);
            perlin_generate_perm(perm_z);
        }

        double noise(const Point3d &p) const {
            
            auto u = p.x() - std::floor(p.x());
            auto v = p.y() - std::floor(p.y());
            auto w = p.z() - std::floor(p.z());

            auto i = int(std::floor(p.x()));
            auto j = int(std::floor(p.y()));
            auto k = int(std::floor(p.z()));

            Vector3d c[2][2][2];
            for (int di = 0; di < 2; di++)
                for (int dj = 0; dj < 2; dj++)
                    for (int dk = 0; dk < 2; dk++)
                        c[di][dj][dk] = random_vector[
                             perm_x[(i+di) & 255] ^ 
                             perm_y[(j+dj) & 255] ^ 
                             perm_z[(k+dk) & 255] ];

            return perlin_interpolate(c, u, v, w);
        }

        double turb(const Point3d &p, int depth) const {
            double result = 0.0;
            auto temp_p = p;
            double weight = 1.0;
            for (int i = 0; i < depth; i++) {
                result += weight * noise(temp_p);
                temp_p *= 2; // introduce high-frequency noise to complicate the turbulence.
                weight *= 0.5; // lower weight for higher frequency noise avoids its dominance above all.
            }

            return std::fabs(result); // avoid negative values.
        }

    private:
        static const int point_count = 256; // period length of fake-random number generation.
        Vector3d random_vector[point_count]; // stores randomly generated unit vectors.
        int perm_x[point_count]; // stores the disturbed indices on x-direction.
        int perm_y[point_count]; // stores the disturbed indices on y-direction.
        int perm_z[point_count]; // stores the disturbed indices on z-direction.

        static void perlin_generate_perm(int *arr) {
            for (int i = 0; i < point_count; i++)
                arr[i] = i;

            permute(arr, point_count);
        }

        // use Fisher-Yates shuffle algorithm to permute the index values of arr with given length n.
        static void permute(int *arr, int n) {
            int target, temp;
            for (int i = n-1; i > 0; i--) {
                target = sample_int(0, i); // only exchange between those untouched ones.
                temp = arr[i];
                arr[i] = arr[target];
                arr[target] = temp;
            }
        }

        static double perlin_interpolate(Vector3d c[2][2][2], double u, double v, double w) {

            // Hermite cubic interpolation could smooth the transition between color edges.
            u = u*u*(3-2*u);
            v = v*v*(3-2*v);
            w = w*w*(3-2*w);

            auto result = 0.0;
            Vector3d weight_vector;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++) {
                        weight_vector = Vector3d(u-i, v-j, w-k);
                        result += (i*u + (1-i)*(1-u))
                                * (j*v + (1-j)*(1-v))
                                * (k*w + (1-k)*(1-w))
                                * dotProduct(c[i][j][k], weight_vector);
                    }
            
            return result;
        }
};

#endif