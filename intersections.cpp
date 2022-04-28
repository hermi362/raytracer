#include "intersections.h"


// Return a collection of t values where the ray r intersects the sphere
std::vector<Isect> intersect(Ray r, Sphere* pSph) {
  // for details of algorithm, see
  // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection

  // transform ray by inverse of sphere's transform
  r = r.transform(pSph->mTransform.inverse());

  // get vector from sphere centre to ray origin
  // (sphere is centered at 0,0,0)
  Vector vSphereToRay = r.getOrigin() - Point(0,0,0);

  auto a = r.getDirection().dot(r.getDirection());
  auto b = 2 * r.getDirection().dot(vSphereToRay);
  auto c = vSphereToRay.dot(vSphereToRay) - 1;

  auto discriminant = b*b - 4*a*c;

  std::vector<Isect> ret; // create emtpy return vector

  if (discriminant < 0) // no intersections found
    return ret;

  auto t1 = (-b - sqrt(discriminant)) / (2*a);
  auto t2 = (-b + sqrt(discriminant)) / (2*a);

  Isect i1(t1, pSph); 
  Isect i2(t2, pSph);

  if (t1 <= t2) {
    ret.push_back(i1);
    ret.push_back(i2);
  } else {
    ret.push_back(i2);  // reverse the order
    ret.push_back(i1);
  }
  // postcond: elements are in ascending order

  return ret;
}


// Takes a collection of intersections and returns the one that is visible
Isect hit(const std::vector<Isect>& xs) {
  Isect minHit = NULLISECT;  // keep track of Isect with lowest non-neg t-value

  auto i = xs.begin(); // create an iterator
  while (i != xs.end()) {
    if (i->tVal > 0) {
      if (minHit == NULLISECT) {  // this is the first non-neg intersection found
        // minHit.tVal = i->tVal;
        // minHit.obj  = i->obj;
        minHit = *i;
      }
      else if (i->tVal < minHit.tVal) {  // this is a better non-neg intersection
        // minHit.tVal = i->tVal;
        // minHit.obj  = i->obj;
        minHit = *i;
      }
    }
    i++;
  }

  return minHit;
}