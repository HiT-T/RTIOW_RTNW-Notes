#ifndef TEXTURE_H
#define TEXTURE_H

class Texture {
    public:
        virtual ~Texture() = default;

        virtual Color get_texColor(double u, double v, const Vector3d &p) const = 0;
};

class SolidColorTexture : public Texture {
    public:
        SolidColorTexture(const Color &albedo) : albedo(albedo) {}

        SolidColorTexture(double r, double g, double b) : albedo(Color(r,g,b)) {}

        Color get_texColor(double u, double v, const Vector3d &p) const override {
            return albedo;
        }

    private:
        Color albedo;
};

// a checker solid texture.
class CheckerTexture : public Texture {
    public:
        CheckerTexture(double scale, shared_ptr<Texture> odd, shared_ptr<Texture> even)
          : invScale(1.0 / scale), odd(odd), even(even) {}

        CheckerTexture(double scale, const Color &c1, const Color &c2)
          : CheckerTexture(scale, make_shared<SolidColorTexture>(c1), make_shared<SolidColorTexture>(c2)) {}

        Color get_texColor(double u, double v, const Vector3d &p) const override {
            auto x_int = int(std::floor(invScale * p.x()));
            auto y_int = int(std::floor(invScale * p.y()));
            auto z_int = int(std::floor(invScale * p.z()));

            bool isOdd = (x_int + y_int + z_int) % 2 == 1;
            
            return isOdd ? odd->get_texColor(u, v, p) : even->get_texColor(u, v, p);
        }

    private:
        double invScale;
        shared_ptr<Texture> odd;
        shared_ptr<Texture> even;      
};

#endif