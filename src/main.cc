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
    auto material_ground = make_shared<Diffuse>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Diffuse>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Dielectric>(1.50);
    auto material_bubble = make_shared<Dielectric>(1.00 / 1.50); // because defaultly assume enclosing as air, thus need divided by 1.50.
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    // assign mateials to newly created objects, and add them to the scene.
    scene.add(make_shared<Sphere>(Point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<Sphere>(Point3d( 0.0,    0.0, -1.2),   0.5, material_center));
    scene.add(make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.4, material_bubble));
    scene.add(make_shared<Sphere>(Point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    // define camera params.
    scene.vfov     = 20;
    scene.eye_pos  = Point3d(-2, 2, 1);
    scene.gaze_pos = Point3d(0, 0, -1);
    scene.up_dir   = Vector3d(0, 1, 0);

    // define renderer and image size.
    Renderer r;
    r.spp = 100;

    // render the image.
    auto start = std::chrono::system_clock::now();
    r.render(scene);
    auto stop = std::chrono::system_clock::now();

    std::cout << "\nDone!\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << "h";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << "min";
    std::cout << " : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << "s\n";

    return 0;
}