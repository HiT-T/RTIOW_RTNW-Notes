#ifndef PERLIN_H
#define PERLIN_H

class Perlin {
    public:
        Perlin() {
            for (int i = 0; i < point_count; i++) {
                random_double[i] = sample_double();
            }
            
            perlin_generate_perm(perm_x);
            perlin_generate_perm(perm_y);
            perlin_generate_perm(perm_z);
        }

        double noise(const Point3d &p) const {
            auto u = p.x() - std::floor(p.x());
            auto v = p.y() - std::floor(p.y());
            auto w = p.z() - std::floor(p.z());

            // Hermite cubic interpolation could smooth the transition between color edges.
            u = u*u*(3-2*u);
            v = v*v*(3-2*v);
            w = w*w*(3-2*w);

            auto i = int(std::floor(p.x()));
            auto j = int(std::floor(p.y()));
            auto k = int(std::floor(p.z()));

            double c[2][2][2];
            for (int di = 0; di < 2; di++)
                for (int dj = 0; dj < 2; dj++)
                    for (int dk = 0; dk < 2; dk++)
                        c[di][dj][dk] = random_double[
                             perm_x[(i+di) & 255] ^ 
                             perm_y[(j+dj) & 255] ^ 
                             perm_z[(k+dk) & 255] ];

            // use trilinear interpolation to smooth the noise.
            return trilerp(c, u, v, w);
        }

    private:
        static const int point_count = 256; // period length of fake-random number generation.
        double random_double[point_count]; // stores the fake-random generated numbers.
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

        static double trilerp(double c[2][2][2], double u, double v, double w) {
            auto result = 0.0;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        result += (i*u + (1-i)*(1-u))
                                * (j*v + (1-j)*(1-v))
                                * (k*w + (1-k)*(1-w))
                                * c[i][j][k];
            
            return result;
        }
};

#endif