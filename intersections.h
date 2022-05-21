#pragma once

#include <vector>
#include "ray.h"
#include "sphere.h"
#include "util.h"


//  calculates intersections of ray and shpere
bool intersect(Ray r, Sphere* pSph, float& thit);

