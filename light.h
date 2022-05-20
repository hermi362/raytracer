#pragma once

#include "point.h"
#include "color.h"

// defines a point light source in the scene
struct PointLight
{
  Point position;
  Color intensity;

  PointLight(Point p, Color i): position(p), intensity(i) {}
  
};
