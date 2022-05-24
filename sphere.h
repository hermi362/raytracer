#pragma once

#include "matrix.h"
#include "vector.h"
#include "material.h"
#include "ray.h"

struct Sphere
{
    // transformation to place/deform the sphere in scene (object2world) 
    Matrix objectToWorld = id4Matrix; 
    Matrix worldToObject = id4Matrix; 
    Material material;

    Sphere() {}  // origin at (0,0,0) with unit radius

    void setTransform(Matrix m) {
        objectToWorld = m;
        worldToObject = m.inverse();
    }

    // get the world surface normal vector at some world point p on the surface
    Vector getNormalAt(Point worldp) {
        Point objectp = worldToObject * worldp;
        Vector objectn = (objectp - Point(0,0,0));
        Vector worldn = worldToObject.transpose() * objectn;        
        return worldn.normalize();
    }

    // Ray-sphere intersection. 
    // returns false if ray misses sphere
    // returns thit, the nearest t-value of the intersection
    // for details of algorithm, see
    // https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
    bool intersect(const Ray& worldRay, float& thit);

};
