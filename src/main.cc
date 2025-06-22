#include "color.h"
#include "vec3d.h"

#include <iostream>

int main() {
    
    // define .ppm image size.
    int image_width = 256, image_height = 256;

    // store RGB color values into the .ppm.
     FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

    for (auto j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (auto i = 0; i < image_width; i++) {
            auto pixel_color = Color(double(i) / image_width, double(j) / image_height, .0);
            write_color(fp, pixel_color);
        }
    }
    
    fclose(fp);
    std::clog << "\rDone.                 \n";
}