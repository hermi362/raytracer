#pragma once

#include <vector>
#include "ray.h"

class Sphere
{
  private:

  public:
    Sphere() {}  // origin at (0,0,0) with unit radius

    // Return the collection of t values where the ray r intersects this sphere
    std::vector<float> intersect(Ray r) const;
};