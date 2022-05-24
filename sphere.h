#pragma once

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "ray.h"

class Sphere : public Shape
{
public:
  Sphere() : Shape() {}  // origin at (0,0,0) with unit radius

  // get the world surface normal vector at some world point p on the surface
  Vector getNormalAt(const Point& worldp) const;

  // Ray-sphere intersection. 
  // returns false if ray misses sphere
  // returns thit, the nearest t-value of the intersection
  // for details of algorithm, see
  // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
  bool intersect(const Ray& worldRay, float& tHit) const;

};
