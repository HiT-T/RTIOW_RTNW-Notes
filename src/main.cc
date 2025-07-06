#include "global.h"

#include "Object.h"
#include "Sphere.h"
#include "quad.h"
#include "BVH.h"
#include "Scene.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer.h"

void bouncing_spheres() {
    
    // create the scene with image size params.
    Scene scene(400, 16.0 / 9.0);

    // define materials.
    auto checker_texture = make_shared<CheckerTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));
    scene.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, make_shared<Diffuse>(checker_texture)));

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

    // build BVH for added objects.
    scene.buildBVH();

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
}

void checkered_spheres() {

    Scene scene(400, 16.0 / 9.0);

    auto checker_texture = make_shared<CheckerTexture>(0.32, Color(.2, .3, .1), Color(.9, .9, .9));

    scene.add(make_shared<Sphere>(Point3d(0,-10, 0), 10, make_shared<Diffuse>(checker_texture)));
    scene.add(make_shared<Sphere>(Point3d(0, 10, 0), 10, make_shared<Diffuse>(checker_texture)));

    scene.buildBVH();

    scene.vfov      = 20;
    scene.eye_pos   = Point3d(13,2,3);
    scene.gaze_pos  = Point3d(0,0,0);
    scene.up_dir    = Vector3d(0,1,0);

    scene.defocus_angle = 0;

    Renderer r;
    r.spp = 256;

    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() % 60 << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() % 60 << "s\n";
}

void earth() {

    Scene scene(400, 16.0 / 9.0);

    auto earth_texture = make_shared<ImageTexture>("earthmap.jpg");
    auto earth_material = make_shared<Diffuse>(earth_texture);
    scene.add(make_shared<Sphere>(Point3d(0,0,0), 2, earth_material));

    scene.buildBVH();

    scene.vfov      = 20;
    scene.eye_pos   = Point3d(0,0,12);
    scene.gaze_pos  = Point3d(0,0,0);
    scene.up_dir    = Vector3d(0,1,0);

    scene.defocus_angle = 0;

    Renderer r;
    r.spp = 100;

    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() % 60 << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() % 60 << "s\n";
}

void perlin_spheres() {
    Scene scene(400, 16.0 / 9.0);

    auto perlin_texture = make_shared<NoiseTexture>(4);
    scene.add(make_shared<Sphere>(Point3d(0,-1000,0), 1000, make_shared<Diffuse>(perlin_texture)));
    scene.add(make_shared<Sphere>(Point3d(0,2,0), 2, make_shared<Diffuse>(perlin_texture)));

    scene.buildBVH();

    scene.vfov      = 20;
    scene.eye_pos   = Point3d(13,2,3);
    scene.gaze_pos  = Point3d(0,0,0);
    scene.up_dir    = Vector3d(0,1,0);

    scene.defocus_angle = 0;

    Renderer r;
    r.spp = 100;

    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() % 60 << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() % 60 << "s\n";
}

void quads() {
    Scene scene(400, 1.0);

    // Materials
    auto left_red     = make_shared<Diffuse>(Color(1.0, 0.2, 0.2));
    auto back_green   = make_shared<Diffuse>(Color(0.2, 1.0, 0.2));
    auto right_blue   = make_shared<Diffuse>(Color(0.2, 0.2, 1.0));
    auto upper_orange = make_shared<Diffuse>(Color(1.0, 0.5, 0.0));
    auto lower_teal   = make_shared<Diffuse>(Color(0.2, 0.8, 0.8));

    // Quads
    scene.add(make_shared<Quad>(Point3d(-3,-2, 5), Vector3d(0, 0,-4), Vector3d(0, 4, 0), left_red));
    scene.add(make_shared<Quad>(Point3d(-2,-2, 0), Vector3d(4, 0, 0), Vector3d(0, 4, 0), back_green));
    scene.add(make_shared<Quad>(Point3d( 3,-2, 1), Vector3d(0, 0, 4), Vector3d(0, 4, 0), right_blue));
    scene.add(make_shared<Quad>(Point3d(-2, 3, 1), Vector3d(4, 0, 0), Vector3d(0, 0, 4), upper_orange));
    scene.add(make_shared<Quad>(Point3d(-2,-3, 5), Vector3d(4, 0, 0), Vector3d(0, 0,-4), lower_teal));

    scene.buildBVH();

    scene.vfov      = 80;
    scene.eye_pos   = Point3d(0,0,9);
    scene.gaze_pos  = Point3d(0,0,0);
    scene.up_dir    = Vector3d(0,1,0);

    scene.defocus_angle = 0;

    Renderer r;
    r.spp = 100;

    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() % 60 << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() % 60 << "s\n";
}

int main() {
    int scene_index = 4;
    switch(scene_index) {
        case 0: bouncing_spheres(); break;
        case 1: checkered_spheres(); break;
        case 2: earth(); break;
        case 3: perlin_spheres(); break;
        case 4: quads(); break;
    }
}