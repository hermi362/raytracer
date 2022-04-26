#include "sphere.h"
#include <vector>

std::vector<float> Sphere::intersect(Ray r) const {
  // for details of algorithm, see
  // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

  // get vector from sphere centre to ray origin
  // (sphere is centered at 0,0,0)
  Vector vSphereToRay = r.getOrigin() - Point(0,0,0);

  auto a = r.getDirection().dot(r.getDirection());
  auto b = 2 * r.getDirection().dot(vSphereToRay);
  auto c = vSphereToRay.dot(vSphereToRay) - 1;

  auto discriminant = b*b - 4*a*c;

  std::vector<float> ret; // create emtpy return vector

  if (discriminant < 0) // no intersections found
    return ret;

  auto t1 = (-b - sqrt(discriminant)) / (2*a);
  auto t2 = (-b + sqrt(discriminant)) / (2*a);

  if (t1 <= t2) {
    ret.push_back(t1);
    ret.push_back(t2);
  } else {
    ret.push_back(t2);  // reverse the order
    ret.push_back(t1);
  }
  // postcond: elements are in ascending order

  return ret;
}