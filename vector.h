#pragma once

#include "point.h"
#include <cmath>

struct Vector {
  float x, y, z, w;

  Vector(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {} 
  Vector(float _x, float _y, float _z)           : Vector(_x, _y, _z, 0.0f) {} 
  Vector() : Vector(0.0f, 0.0f, 0.0f, 0.0f) {}

  Vector(Point p) : Vector(p.x, p.y, p.z) {} 

  float magnitude() {return std::sqrt(x*x + y*y + z*z + w*w);}

  Vector normalize() {
      float mag = this->magnitude();
      return Vector(x/mag, y/mag, z/mag, 0.0f);
  }

  float dot(const Vector& v) {
      return x*v.x + y*v.y + z*v.z + w*v.w;
  }

  Vector cross(const Vector& v) {
      // left-handed cross product
      return Vector(
          y*v.z - z*v.y,
          z*v.x - x*v.z,
          x*v.y - y*v.x, 
          0.0f);
  }

  // negation operator
  Vector operator-() { return Vector(-x, -y, -z, -w); }
};

inline bool operator==(const Vector& lhs, const Vector& rhs) {
  return (isEqualEnough(lhs.x, rhs.x) && 
      isEqualEnough(lhs.y, rhs.y) && 
      isEqualEnough(lhs.z, rhs.z) && 
      isEqualEnough(lhs.w, rhs.w) );
}
inline bool operator!=(const Vector& lhs, const Vector& rhs) {
  return !(lhs==rhs);
}



  // adding a point and a vector (in either order) yields a point
inline Point operator+(const Point& p, const Vector& v) {
  return Point(p.x+v.x, p.y+v.y, p.z+v.z);
}
inline Point operator+(const Vector& v, const Point& p) {
  return Point(p.x+v.x, p.y+v.y, p.z+v.z);
}

// adding two vectors yields a vector
inline Vector operator+(const Vector& lhs, const Vector& rhs) {
  return Vector(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z, 0.0f);
}
inline Vector operator-(const Vector& lhs, const Vector& rhs) {
  return Vector(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, 0.0f);
}

// scalar multiplication/division
inline Vector operator*(float a, const Vector& v) {
    return Vector(v.x * a, v.y * a, v.z * a, v.w * a); 
}
inline Vector operator*(const Vector& v, float a) {
    return Vector(v.x * a, v.y * a, v.z * a, v.w * a); 
}
inline Vector operator/(const Vector& t, float a) {
    return Vector(t.x / a, t.y / a, t.z / a, t.w / a);
}


