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
            // 4* can discretize the coords, increase noise frequency, and produces more details.
            // & 255 == % 256, which controls the indices in a given range.
            auto i = int(4*p.x()) & 255; 
            auto j = int(4*p.y()) & 255;
            auto k = int(4*p.z()) & 255;

            // XOR between permuted indices of distinct axis adds to randomness of resulting index.
            return random_double[perm_x[i] ^ perm_y[j] ^ perm_z[k]];
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
};

#endif