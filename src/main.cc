#include "global.h"

#include "Object.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Renderer.h"

int main() {

    // create the scene and add objects.
    Scene scene;

    auto material_ground = make_shared<Diffuse>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Diffuse>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<Metal>(Color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);

    scene.add(make_shared<Sphere>(Point3d( 0.0, -100.5, -1.0), 100.0, material_ground));
    scene.add(make_shared<Sphere>(Point3d( 0.0,    0.0, -1.2),   0.5, material_center));
    scene.add(make_shared<Sphere>(Point3d(-1.0,    0.0, -1.0),   0.5, material_left));
    scene.add(make_shared<Sphere>(Point3d( 1.0,    0.0, -1.0),   0.5, material_right));

    // define renderer and image size.
    Renderer r;
    r.aspect_ratio = 16.0 / 9.0;
    r.image_width = 400;
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