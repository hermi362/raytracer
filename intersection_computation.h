#pragma once

#include "ray.h"
#include "shape.h"

// class with a silly name, based on the same name used in the Ray Tracer Challenge book
// This class caches pre-computed data about a ray-object intersection.
class IntersectionComputation {
public:
  IntersectionComputation(const Ray& r, const float& tHit, Shape* pShape) {
    time = tHit;
    this->pShape = pShape;
    point = r.getPosition(tHit);
    eyev = -r.getDirection();
    normalv = pShape->getNormalAt(point);
    if (normalv.dot(eyev) < 0) {
      inside = true;
      normalv = -normalv;
    } else {
      inside = false;
    }
  }

  // data members
  float time;
  Shape* pShape;
  Point point;
  Vector eyev;
  Vector normalv;
  bool inside;
};