#include "ray.h"

// Compute the position of this ray at the distance t along the ray
Point Ray::getPosition(float t) {
  return origin + (t * direction);
}

// return a new ray after applying transformation
Ray Ray::transform(const Matrix& m) {
  Ray ret;

  ret.origin = m * origin;
  ret.direction = m * direction;
  
  return ret;
}

Vector reflect(const Vector& in, const Vector& normal) {
  return in - normal * 2.0f * in.dot(normal);
}
