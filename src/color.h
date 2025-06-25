#ifndef COLOR_H
#define COLOR_H

using Color = Vector3d;

// conver data from linear space (radiance) to gamma space (RGB color).
inline double linear_to_gamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }

    return 0.0;
}

void write_color(FILE*& fp, const Vector3d& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    static unsigned char color[3];
    static const Interval intensity(1e-3,.999);
    color[0] = unsigned char(255.999 * intensity.clamp(r));
    color[1] = unsigned char(255.999 * intensity.clamp(g));
    color[2] = unsigned char(255.999 * intensity.clamp(b));

    fwrite(color, 1, 3, fp);
}

#endif