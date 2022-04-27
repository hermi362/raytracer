#include <vector>
#include "ray.h"
#include "sphere.h"

// encapsulates a ray-object intersection
struct Isect {
  float tVal;
  Sphere* obj; // TODO: make this a base class common to all types of shape

  Isect(float t, Sphere* o) : tVal(t), obj(o) {}
};

//  calculates intersections of ray and shpere
std::vector<Isect> intersect(Ray r, Sphere* pSph);