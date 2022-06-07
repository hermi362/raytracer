#pragma once

#include "point.h"
#include "matrix.h"
#include "material.h"
#include "ray.h"

// common base class for sphere, triangle, etc.
class Shape
{
public:
  
  Matrix objectToWorld;  // transformation to place/deform the shape in scene 
  Matrix worldToObject;  // the inverse transformation (cached for performance)
  Material material;

  Shape() : objectToWorld(id4Matrix), worldToObject(id4Matrix) {}

  void setTransform(Matrix m) {
      objectToWorld = m;
      worldToObject = m.inverse();
  }

  // calculate the normal vector at a certain suface point.
  virtual Vector getNormalAt(const Point& worldp) const = 0;

  // cast a ray into shape, return true if ray intersects shape.
  // return ray's t-value in case of intersection
  virtual bool intersect(const Ray& worldRay, float& tHit) const = 0;
};