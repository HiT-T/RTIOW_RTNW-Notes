#ifndef COLOR_H
#define COLOR_H

#include "vec3d.h"

#include <iostream>

using Color = Vec3d;

void write_color(FILE*& fp, const Vec3d& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    static unsigned char color[3];
    color[0] = unsigned char(255.999 * r);
    color[1] = unsigned char(255.999 * g);
    color[2] = unsigned char(255.999 * b);

    fwrite(color, 1, 3, fp);
}

#endif