#pragma once

#include <string>
#include "util.h"

class Color {
public:
  float r, g, b;
  Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
  Color() : Color(0,0,0) {}

  void setColor(const float& _r, const float& _g, const float& _b) {
    r = _r; g = _g; b = _b;
  }
  std::string toString() const {
    const auto N = 50;
    char buffer[N];
    std::snprintf(buffer, N, "COLOR[%f, %f, %f]", r, g, b);
    return buffer;
  }

  bool operator==(const Color& c) const {
    return (isEqualEnough(r, c.r) &&
            isEqualEnough(g, c.g) &&
            isEqualEnough(b, c.b) );
  }
  Color operator+(const Color& c) const {
    return Color(r+c.r, g+c.g, b+c.b);
  }
  Color operator-(const Color& c) const {
    return Color(r-c.r, g-c.g, b-c.b);
  }
  Color operator*(const float a) const {
    return Color(r*a, g*a, b*a);
  }
  Color operator*(const Color& c) const {
    return Color(r*c.r, g*c.g, b*c.b);
  }
};

inline Color operator*(float a, Color c) {
  return c * a;
}


