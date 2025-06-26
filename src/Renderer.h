#ifndef RENDERER_H
#define RENDERER_H

#include "Object.h"
#include "Material.h"

class Renderer {
    public:
        double aspect_ratio = 1.0;
        int image_width = 100;
        int spp = 10; // count of samples per pixel.

        Renderer() {}

        void render(const Object &scene) {
            initialize();

            // calculate and store RGB color values into image.
            FILE* fp = fopen("binary.ppm", "wb");
            (void)fprintf(fp, "P6\n%d %d\n255\n", image_width, image_height);

            std::cout << "SPP: " << spp << "\n";

            for (auto j = 0; j < image_height; j++) {
                for (auto i = 0; i < image_width; i++) {
                    // compute color of the ray/pixel.
                    auto pixel_color = Color();
                    for (int s = 0; s < spp; s++) {
                        auto r = get_ray(i, j);
                        pixel_color += get_color(r, scene);
                    }

                    // write the computed pixel_color into image.
                    write_color(fp, pixel_color / spp);
                }
                UpdateProgress(j / double(image_height));
            }
            UpdateProgress(1.);
    
            fclose(fp);
        }

        private:
            int image_height = 0;
            Point3d eye_pos;
            double viewport_height = .0, viewport_width = .0;
            double RussianRoulette = 0.8;

            void initialize() {
                image_height = int(image_width / aspect_ratio);
                image_height = image_height < 1 ? 1 : image_height;

                // define camera & viewport related params.
                eye_pos = Point3d(.0,.0,.0);
                viewport_height = 2.0, viewport_width = viewport_height * (double(image_width)/image_height);
            }

            Ray get_ray(int i, int j) const {
                double dx = sample_double();
                double dy = sample_double();

                // compute the viewport coordinates based on image indices.
                auto x = ((i + dx) / double(image_width) - 0.5) * viewport_width;
                auto y = (0.5 - (j + dy) / double(image_height)) * viewport_height;

                // return a ray created based on the direction value.
                auto dir = normalize(Vector3d(x, y, -1));
                return Ray(eye_pos, dir);
            }

            Color get_color(const Ray &ri, const Object &scene) const {
                auto isect = Intersection();

                // if doesn't intersect or (t < .001), return background color.
                // note: (t_min == 1e-3 (> 0)) avoids self-intersection caused by floating point rounding errors.
                if (!scene.intersect(ri, Interval(1e-3, infinity), isect)) {
                    auto a = 0.5 + ri.direction().y() / viewport_height;
                    return (1-a) * Color(1.0,1.0,1.0) + a * Color(0.5,0.7,1.0);
                }

                // test RR to decide if continues bouncing.
                if (sample_double() > RussianRoulette) { return Color(); }

                // if RR passes, compute radiance by recursively self-calling, which contains direct & indirect illumination.
                Color attenuation; Ray ro;
                if (isect.m->scatter(ri, isect, attenuation, ro)) {
                    return attenuation * get_color(ro, scene) / RussianRoulette;
                }

                // if the material doesn't scatter, stop ray tracing and return black color.
                return Color();
            }
};

#endif