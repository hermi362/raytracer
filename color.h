#pragma once

#include <string>

class Color {
public:
  float r, g, b;
  Color(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
  Color() : Color(0,0,0) {}

  void setColor(const float& _r, const float& _g, const float& _b) {
    r = _r; g = _g; b = _b;
  }
  std::string toString() {
    const auto N = 50;
    char buffer[N];
    std::snprintf(buffer, N, "COLOR[%f, %f, %f]", r, g, b);
    return buffer;
  }

  bool operator==(const Color& c) {
    static const float ERR = 0.00001;  // permissible error below which two floating-point values are considered equal
    return (std::abs(r - c.r) < ERR  &&
            std::abs(g - c.g) < ERR  &&
            std::abs(b - c.b) < ERR    );
  }
  Color operator+(const Color& c) {
    return Color(r+c.r, g+c.g, b+c.b);
  }
  Color operator-(const Color& c) {
    return Color(r-c.r, g-c.g, b-c.b);
  }
  Color operator*(const float a) {
    return Color(r*a, g*a, b*a);
  }
  Color operator*(const Color& c) {
    return Color(r*c.r, g*c.g, b*c.b);
  }
};

inline Color operator*(float a, Color c) {
  return c * a;
}


