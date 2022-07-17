#pragma once

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "ray.h"

class Triangle : public Shape
{
public:
  Triangle(Point p0, Point p1, Point p2) : 
    p0(p0), p1(p1), p2(p2) {}

  // return the triangle normal vector, ignore the input argument
  Vector getNormalAt(const Point& worldp) const;

  // return true if ray intersects triangle (inside triangle bounds).
  // return ray's t-value in case of intersection
  // algorithm derived from:
  // https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
  bool intersect(const Ray& worldRay, float& tHit) const;


  // data members:
  Point p0, p1, p2;  // the triangle vertices
};