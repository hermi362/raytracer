#include "ray.h"

// Compute the position of this ray at the distance t along the ray
Point Ray::getPosition(float t) {
  return origin + t * direction;
}
