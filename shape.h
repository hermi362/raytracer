#pragma once

#include "point.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"

// common base class for sphere, triangle, etc.
class Shape
{
public:
  // transformation to place/deform the shape in scene (object2world) 
  Matrix objectToWorld;
  Matrix worldToObject;
  Material material;

  Shape() : objectToWorld(id4Matrix), worldToObject(id4Matrix) {}

  void setTransform(Matrix m) {
      objectToWorld = m;
      worldToObject = m.inverse();
  }

  virtual Vector getNormalAt(const Point& worldp) const = 0;

  virtual bool intersect(const Ray& worldRay, float& tHit) const = 0;
};