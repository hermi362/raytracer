#pragma once

#include <cmath>
#include <cassert>

class Tuple {
public:
  float x, y, z, w;
  Tuple(float _x, float _y, float _z, float _w) {x=_x, y=_y, z=_z, w=_w;}
  Tuple(): Tuple(0, 0, 0, 0) {}
  std::string toString() {
    const int N = 50;
    char buffer[N];

    std::snprintf(buffer, N, "(%.3f %.3f %.3f    %.0f)", x,y,z,w);
    return buffer;
  }
  Tuple operator-() {return Tuple(0-this->x, 0-this->y, 0-this->z, 0-this->w);} // negation operator
};

inline bool operator==(const Tuple& lhs, const Tuple& rhs) {
  static const float ERR = 0.00001;  // permissible error below which two floating-point values are considered equal
  if (std::abs(lhs.x - rhs.x) < ERR  &&
      std::abs(lhs.y - rhs.y) < ERR  &&
      std::abs(lhs.z - rhs.z) < ERR  &&
      std::abs(lhs.w - rhs.w) < ERR)
    return true;
  else
    return false;
}
inline bool operator!=(const Tuple& lhs, const Tuple& rhs) {
  return !(lhs==rhs);
}

inline Tuple operator+(Tuple lhs, const Tuple& rhs) {
  // according to reference pages, passing lhs by value helps optimize chained a+b+c
  return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}
inline Tuple operator-(Tuple lhs, const Tuple& rhs) {
  // according to reference pages, passing lhs by value helps optimize chained a-b-c
  return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}
inline Tuple operator*(const Tuple& t, float a) {
    return Tuple(t.x * a, t.y * a, t.z * a, t.w * a);
}
inline Tuple operator*(float a, const Tuple& t) {
    return  t * a;  // operator*(t, a);
}
inline Tuple operator/(const Tuple& t, float a) {
    assert(a != 0.0);
    return Tuple(t.x / a, t.y / a, t.z / a, t.w / a);
}

class Point : public Tuple {
public:
  Point(float _x, float _y, float _z) : Tuple(_x, _y, _z, 1.0){} 
  Point() : Point(0, 0, 0){}
};

class Vector : public Tuple {
public:
  Vector(float _x, float _y, float _z) : Tuple(_x, _y, _z, 0.0){} 
  Vector() : Vector(0, 0, 0){}
  float magnitude() {return std::sqrt(x*x + y*y + z*z + w*w);}
  Vector normalize() {
      auto mag = this->magnitude();
      return Vector(x/mag, y/mag, z/mag);
  }
  float dot(const Vector& v) {
      return x*v.x + y*v.y + z*v.z + w*v.w;
  }
  Vector cross(const Vector& v) {
      // left-handed cross product
      return Vector(
          y*v.z - z*v.y,
          z*v.x - x*v.z,
          x*v.y - y*v.x);
  }
};

// adding a point and a vector (in either order) yields a point
inline Point operator+(const Point& p, const Vector& v) {
  return Point(p.x+v.x, p.y+v.y, p.z+v.z);
}
inline Point operator+(const Vector& v, const Point& p) {
  return p + v;
}

// adding two vectors yields a vector
inline Vector operator+(const Vector& lhs, const Vector& rhs) {
  return Vector(lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z);
}