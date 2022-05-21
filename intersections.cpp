#include "intersections.h"
#include "util.h"


// Ray-sphere intersection. 
// returns false if ray misses sphere
// returns thit, the nearest t-value of the intersection
// for details of algorithm, see
// https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
bool intersect(Ray r, Sphere* pSph, float& thit) {

  // transform ray by inverse of sphere's transform
  r = r.transform(pSph->mTransform.inverse());

  // get vector from sphere centre to ray origin
  // (sphere is centered at 0,0,0)
  Vector vSphereToRay = r.getOrigin() /* - Point(0,0,0)*/;

  float a = r.getDirection().dot(r.getDirection());
  float b = 2 * r.getDirection().dot(vSphereToRay);
  float c = vSphereToRay.dot(vSphereToRay) - 1;
  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) // no intersections found
    return false;


  // float t1 = (-b - sqrt(discriminant)) / (2*a);
  // float t2 = (-b + sqrt(discriminant)) / (2*a);
  // optimized version of the above calculations for t1, t2:
  float root_disc_over_a = sqrt(discriminant) / a;
  float t1 = -0.5 * (b/a + root_disc_over_a);
  float t2 = t1 + root_disc_over_a;

  thit = min(t1, t2);
  return true;
}


