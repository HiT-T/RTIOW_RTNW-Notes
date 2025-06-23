#include "Sphere.h"
#include "Object.h"
#include "Color.h"
#include "Ray.h"
#include "Vector3d.h"

#include <iostream>

int main() {
    
    // define image size.
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400, image_height = int(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // define camera & viewport related params.
    auto eye_pos = Point3d(.0,.0,.0);
    auto viewport_height = 2.0, viewport_width = viewport_height * (double(image_width)/image_height);

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
            auto dir = normalize(Vector3d(x, y, -1));
            auto r = Ray(eye_pos, dir);

            // compute color of the ray/pixel.
            auto pixel_color = Color();
            auto s = Sphere(Point3d(0,0,-1), 0.5);
            auto isect = Intersection();
            // if intersect and the closest intersection has a positive t.
            if (s.intersect(r, 0, std::numeric_limits<double>::infinity(), isect)) {
                Vector3d N = isect.normal;
                pixel_color = 0.5 * Color(N.x()+1,N.y()+1,N.z()+1);
            } else {
                auto a = 0.5 + r.direction().y() / viewport_height;
                pixel_color = (1-a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
            }

            // write the computed pixel_color into image.
            write_color(fp, pixel_color);
        }
    }
    
    fclose(fp);
    std::clog << "\rDone.                 \n";
}