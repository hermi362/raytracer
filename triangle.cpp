#include "triangle.h"
#include "ray.h"
#include "util.h"

Vector Triangle::getNormalAt(const Point& worldp) const {
  Vector n = (p1-p0).cross(p2-p0);
  n = n.normalize();
  // TODO: consider caching the normal as a class member
  return n;
}

bool Triangle::intersect(const Ray& worldRay, float& tHit) const {

  // transform ray to object coordinate system
  Ray r = worldRay.transform(worldToObject);

  Vector lab = r.getDirection();
  Vector p01 = p1 - p0;
  Vector p02 = p2 - p0;
  Point la = r.getOrigin();

  Matrix mat(3, {-lab.x, p01.x, p02.x,
                 -lab.y, p01.y, p02.y,
                 -lab.z, p01.z, p02.z});

  // a zero determinant means the ray is either in the triangle's plane or outside but parallel to it
  if ( isEqualEnough(mat.determinant(), 0.f) ) 
    return false;

  // TODO: test performance of general-purpose matrix inversion against a hard-coded solution
  mat = mat.inverse();
  Vector lp = (la - p0);
  tHit    = mat.at(0, 0) * lp.x  +  mat.at(0, 1) * lp.y  +  mat.at(0, 2) * lp.z;
  float u = mat.at(1, 0) * lp.x  +  mat.at(1, 1) * lp.y  +  mat.at(1, 2) * lp.z;
  float v = mat.at(2, 0) * lp.x  +  mat.at(2, 1) * lp.y  +  mat.at(2, 2) * lp.z;

  if ( tHit > MaxFloat  ||  u < 0.f  ||  v < 0.f  || u+v > 1.f )
    return false;
  else
    return true;
}
