#include "color.h"
#include "ray.h"
#include "vec3d.h"

#include <iostream>

bool hitSphere(const Vec3d& C, double radius, const Ray& r) {
    Vec3d d = r.direction(), qc = C - r.origin();
    auto a = dotProduct(d, d);
    auto b = -2 * dotProduct(d, qc);
    auto c = dotProduct(qc, qc) - radius*radius;
    return (b*b - 4*a*c >= 0);
}

int main() {
    
    // define image size.
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400, image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // define camera & viewport related params.
    auto eye_pos = Point3d(.0,.0,.0);
    auto viewport_width = 2.0, viewport_height = viewport_width / (double(image_width)/image_height);

    // store RGB color values into image.
     FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

    for (auto j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (auto i = 0; i < image_width; i++) {
            // compute the viewport coordinates based on image indices.
            auto x = ((i + 0.5) / image_width - 0.5) * viewport_width;
            auto y = (0.5 - (j + 0.5) / image_height) * viewport_height;

            // create a ray based on the direction value.
            auto dir = normalized(Vec3d(x, y, -1));
            auto r = Ray(eye_pos, dir);

            // compute color of the ray.
            auto pixel_color = Color();
            if (hitSphere(Point3d(0,0,-1), 0.5, r)) {
                pixel_color = Color(1, 0, 0);
            }
            else {
                auto a = 0.5 + r.direction().y() / viewport_height;
                pixel_color = (1-a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
            }

            write_color(fp, pixel_color);
        }
    }
    
    fclose(fp);
    std::clog << "\rDone.                 \n";
}