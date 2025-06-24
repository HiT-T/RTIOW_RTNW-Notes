#include "global.h"

#include "Object.h"
#include "Scene.h"
#include "Sphere.h"
#include "Renderer.h"

int main() {

    // create the scene and add objects.
    Scene scene;
    scene.add(make_shared<Sphere>(Point3d(0,0,-1), 0.5));
    scene.add(make_shared<Sphere>(Point3d(0,-100.5,-1), 100));

    // define renderer and image size.
    Renderer r;
    r.aspect_ratio = 16.0 / 9.0;
    r.image_width = 400;

    // render the image.
    r.render(scene);
}