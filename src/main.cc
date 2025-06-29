#include "global.h"

#include "Object.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Renderer.h"

int main() {

    // create the scene with image size params.
    Scene scene(400, 16.0 / 9.0);

    // define materials.
    auto ground_material = make_shared<Diffuse>(Color(0.5, 0.5, 0.5));
    scene.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_m = sample_double();
            Point3d center(a + 0.9*sample_double(), 0.2, b + 0.9*sample_double());

            if ((center - Point3d(4, 0.2, 0)).norm() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_m < 0.8) {
                    // diffuse
                    auto albedo = Color::sample() * Color::sample();
                    sphere_material = make_shared<Diffuse>(albedo);
                    auto center2 = center + Vector3d(0, sample_double(0,.5), 0);
                    scene.add(make_shared<Sphere>(center, center2, 0.2, sphere_material));
                } else if (choose_m < 0.95) {
                    // metal
                    auto albedo = Color::sample(0.5, 1);
                    auto fuzz = sample_double(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Dielectric>(1.5);
                    scene.add(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Dielectric>(1.5);
    scene.add(make_shared<Sphere>(Point3d(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Diffuse>(Color(0.4, 0.2, 0.1));
    scene.add(make_shared<Sphere>(Point3d(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    scene.add(make_shared<Sphere>(Point3d(4, 1, 0), 1.0, material3));

    // define camera params.
    scene.vfov     = 20;
    scene.eye_pos  = Point3d(13, 2, 3);
    scene.gaze_pos = Point3d(0, 0, 0);
    scene.up_dir   = Vector3d(0, 1, 0);

    scene.defocus_angle = 0.6;
    scene.focal_dist    = 10.0;

    // define renderer and image size.
    Renderer r;
    r.spp = 100;

    // render the image.
    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() % 60 << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() % 60 << "s\n";

    return 0;
}