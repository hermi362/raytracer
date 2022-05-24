#pragma once

#include <vector>
#include "sphere.h"
#include "light.h"

struct Scene
{
  PointLight light;
  std::vector<Sphere> vObjects;  // TODO: general objects, not spheres.

  Scene();

  void createDefaultScene() {
    // build a default scene
    light = PointLight(Point(-10, 10, -10), Color(1,1,1));

    Sphere sph;
    sph.material.color = Color(0.8, 1.0, 0.6);
    sph.material.diffuse = 0.7;
    sph.material.specular = 0.2;
    vObjects.push_back(sph);

    sph.setTransform(getScaling(0.5, 0.5, 0.5)) ;
    vObjects.push_back(sph);
  }
};
