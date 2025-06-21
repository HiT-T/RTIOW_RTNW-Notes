#include <iostream>

int main() {
    
    // define .ppm image size.
    int image_width = 256, image_height = 256;

    // store RGB color values into the .ppm.
     FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

    for (auto j = 0; j < image_height; j++) {
        for (auto i = 0; i < image_width; i++) {
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_height-1);
            auto b = 0.0;

            static unsigned char color[3];
            color[0] = unsigned char(255.999 * r);
            color[1] = unsigned char(255.999 * g);
            color[2] = unsigned char(255.999 * b);

            fwrite(color, 1, 3, fp);
        }
    }
    fclose(fp);
}