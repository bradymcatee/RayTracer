#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
#include <cstdint>
#include <cstring>


// C++ Std Usings

using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}
// RNG based on mt19937; thread_local for potential multithreading.
inline std::mt19937& rng() {
  thread_local static std::mt19937 gen(1337); // deterministic default
  return gen;
}
inline void seed_rng(uint64_t seed) {
  rng().seed(seed);
}
inline uint64_t non_deterministic_seed() {
  std::random_device rd;
  uint64_t s = (uint64_t(rd()) << 32) ^ uint64_t(rd());
  return s;
}
inline double random_double() {
  // Returns a random real in [0,1).
  static thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng());
}

inline double random_double(double min, double max) {
  // Returns a random real in [min,max).
  std::uniform_real_distribution<double> dist(min, max);
  return dist(rng());
}

// Common Headers

#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif
