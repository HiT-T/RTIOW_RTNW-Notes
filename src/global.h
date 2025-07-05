#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <chrono>

// C++ Standard Usings.

using std::make_shared;
using std::shared_ptr;

// Constants.

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions.

inline double degrees_to_radians(double degrees) { return (degrees * pi) / 180.0; }

// returns a random double number in [0,1).
inline double sample_double() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

// returns a random double number in [min,max).
inline double sample_double(double min, double max) { return min + (max-min) * sample_double(); }

// returns a random integer in [min,max].
inline int sample_int(int min, int max) { return int(sample_double(min, max+1)); }

inline void UpdateProgress(double progress)
{
    int barWidth = 70;

    std::clog << "[";
    auto pos = int(barWidth * progress);
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::clog << "=";
        else if (i == pos) std::clog << ">";
        else std::clog << " ";
    }
    std::clog << "] " << int(progress * 100.0) << " %\r" << std::flush;
};

// Common Headers.

#include "Interval.h"
#include "Vector3d.h"
#include "Ray.h"
#include "Color.h"

#endif