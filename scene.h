#pragma once

#include <vector>
#include <memory>
#include "sphere.h"
#include "light.h"

class Scene
{
private:
  PointLight light;

  // store pointers to concrete shape objects using managed pointers
  // note: better to use std::make_unique<>() instead of 'new()' when adding to vector
  std::vector<std::unique_ptr<Shape>> vShapes;  

public:
  Scene() {}

  void createDefaultScene();

  // perform ray intersection with every object, return tHit for nearest intersection
  bool intersectScene(const Ray& r, float& tHit);
};
