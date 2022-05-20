#pragma once

#include "matrix.h"
#include "vector.h"

struct Sphere
{
    // transformation to place/deform the sphere in scene (object2world) 
    Matrix mTransform = id4Matrix; 

    Sphere() {}  // origin at (0,0,0) with unit radius

    void setTransform(Matrix m) {
        mTransform = m;
    }

    // get the world surface normal vector at some world point p on the surface
    Vector getNormalAt(Point worldp) {
        Point objectp = mTransform.inverse() * worldp;
        Vector objectn = (objectp - Point(0,0,0));
        Vector worldn = mTransform.inverse().transpose() * objectn;        
        return worldn.normalize();
    }
};
