#pragma once

#include "matrix.h"

struct Sphere
{
    // transformation to place/deform the sphere in scene
    Matrix mTransform = id4Matrix; 

    Sphere() {}  // origin at (0,0,0) with unit radius

    void setTransform(Matrix m) {
        mTransform = m;
    }
};
