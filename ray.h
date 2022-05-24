#pragma once

#include "vector.h"
#include "point.h"
#include "matrix.h"

#include "material.h"
#include "light.h"

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
    Point getOrigin() const  {return origin;}
    Vector getDirection() const {return direction;}

    Point getPosition(float t) const;

    Ray transform(const Matrix& m) const;
};

// compute reflection of incoming vector on surface defined by a normal
Vector reflect(const Vector& in, const Vector& normal);

// perform lighting model calculation
// TODO: consider moving this into a separate module, it's not exactly part of a ray, is it?
Color lighting(Material material, PointLight light, Point position, Vector eyev, Vector normal);