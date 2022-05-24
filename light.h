#pragma once

#include "point.h"
#include "color.h"

// defines a point light source in the scene
struct PointLight
{
  Point position;
  Color intensity;

  PointLight(Point p, Color i): position(p), intensity(i) {}
  PointLight() : PointLight(Point(0,0,0), Color(1,1,1)) {}
};
