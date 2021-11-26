#include "util.h"

bool isEqualEnough(float f1, float f2) {

  const auto TOLERANCE = 0.00001;
  
  auto epsilon = (f1 - f2);
  if (epsilon < 0) 
    epsilon = -epsilon;
  return epsilon < TOLERANCE;
}
