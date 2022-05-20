#include "util.h"

bool isEqualEnough(float f1, float f2) {

  // permissible error below which two floating-point values are considered equal
  static const float TOLERANCE = 0.00001f;
  
  auto epsilon = (f1 - f2);
  if (epsilon < 0) 
    epsilon = -epsilon;
  return epsilon < TOLERANCE;
}

float min(float a, float b) { 
   return a<=b ? a : b; 
}

