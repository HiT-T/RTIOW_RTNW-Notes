#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>

// C++ Standard Usings.

using std::make_shared;
using std::shared_ptr;

// Constants.

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions.

inline double degrees_to_radians(double degrees) { return (degrees * pi) / 180.0; }

// returns a random double number in [0,1).
inline double random_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// returns a random double number in [min,max).
inline double random_double(double min, double max) { return min + (max-min) * random_double(); }

inline void UpdateProgress(double progress)
{
    int barWidth = 70;

    std::clog << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::clog << "=";
        else if (i == pos) std::clog << ">";
        else std::clog << " ";
    }
    std::clog << "] " << int(progress * 100.0) << " %\r" << std::flush;

    if (progress == 1.) { std::clog << "\nDone!\n"; }
};

// Common Headers.

#include "Interval.h"
#include "Vector3d.h"
#include "Ray.h"
#include "Color.h"

#endif