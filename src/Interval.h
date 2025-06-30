#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
    public:
        double min, max;

        Interval() : min(+infinity), max(-infinity) {}
        Interval(double min, double max) : min(min), max(max) {}

        // construct union of two intervals.
        Interval(const Interval &a, const Interval &b) {
            min = std::min(a.min, b.min);
            max = std::max(a.max, b.max);
        }

        double size() const { return max - min; }

        double contains(double t) { return min <= t && t <= max; }

        double surrounds(double t) { return min < t && t < max; }

        double clamp(double x) const { return std::max(min, std::min(max, x)); }
 
        static const Interval empty, universe;
};
const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);

#endif