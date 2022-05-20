#pragma once

#include "util.h"

struct Point {
  float x, y, z, w;

  Point(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
  Point(float _x, float _y, float _z)           : Point(_x, _y, _z, 1.0f) {}
  Point() : Point(0.0f, 0.0f, 0.0f, 1.0f) {}
  
  // negation operator
  Point operator-() { return Point(-x, -y, -z, -w); }
};


inline bool operator==(const Point& lhs, const Point& rhs) {
  return (isEqualEnough(lhs.x, rhs.x) && 
      isEqualEnough(lhs.y, rhs.y) && 
      isEqualEnough(lhs.z, rhs.z) && 
      isEqualEnough(lhs.w, rhs.w) );
}
inline bool operator!=(const Point& lhs, const Point& rhs) {
  return !(lhs==rhs);
}


