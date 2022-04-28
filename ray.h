#pragma once

#include "tuple.h"
#include "matrix.h"

// Implements a ray that will be cast around the scene
class Ray
{
  private:
    Point origin;
    Vector direction;

  public:
    Ray() : Ray(Point(0,0,0), Vector(1,0,0)) {} // default constructor

    Ray(Point ori, Vector dir) :
      origin(ori), direction(dir) {}

    Ray(const Ray &r) :
      origin(r.origin), direction(r.direction) {} // copy constructor

    // TODO: once raytracer is up and running, consider returning origin and direction
    // by reference (as a potentially significant optimization).
    Point getOrigin()  {return origin;}
    Vector getDirection() {return direction;}

    Point getPosition(float t);

    Ray transform(const Matrix& m);
};