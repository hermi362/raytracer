#include "ray.h"

// Compute the position of this ray at the distance t along the ray
Point Ray::getPosition(float t) {
  return origin + Vector(t * direction);
}

// return a new ray after applying transformation
Ray Ray::transform(const Matrix& m) {
  Ray ret;

  ret.origin = m * origin;
  ret.direction = m * direction;
  
  return ret;
}