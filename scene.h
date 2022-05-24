#pragma once

#include <vector>
#include "sphere.h"
#include "light.h"

struct Scene
{
  PointLight light;
  std::vector<Shape&> vShapes;

  Scene();

  void createDefaultScene() {
    // build a default scene
    light = PointLight(Point(-10, 10, -10), Color(1,1,1));

    static Sphere sph1;
    sph1.material.color = Color(0.8, 1.0, 0.6);
    sph1.material.diffuse = 0.7;
    sph1.material.specular = 0.2;
    vShapes.push_back(sph1);

    static Sphere sph2;
    sph2.setTransform(getScaling(0.5, 0.5, 0.5)) ;
    vShapes.push_back(sph2);
  }
};
