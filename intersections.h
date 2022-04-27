#include <vector>
#include "ray.h"
#include "sphere.h"

// encapsulates a ray-object intersection
struct Isect {
  float tVal;
  Sphere* obj; // TODO: make this a base class common to all types of shape

  Isect(float t, Sphere* o) : tVal(t), obj(o) {}

  bool operator==(Isect rhs) {
    return tVal == rhs.tVal && obj == rhs.obj;
  }
};

const static Isect NULLISECT(0.f, nullptr);  // special value used to indicate null result

//  calculates intersections of ray and shpere
std::vector<Isect> intersect(Ray r, Sphere* pSph);

// return visible intersection, or NULLISECT if none found
Isect hit(const std::vector<Isect>& xs);