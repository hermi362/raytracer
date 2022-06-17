#include "scene.h"

void Scene::createDefaultScene() {
  light = PointLight(Point(-10, 10, -10), Color(1,1,1));

  Sphere sph1;
  sph1.material.color = Color(0.8, 1.0, 0.6);
  sph1.material.diffuse = 0.7;
  sph1.material.specular = 0.2;
  vShapes.push_back(std::make_unique<Sphere>(sph1));

  Sphere sph2;
  sph2.setTransform(getScaling(0.5, 0.5, 0.5)) ;
  vShapes.push_back(std::make_unique<Sphere>(sph2));
}

bool Scene::intersectScene(const Ray& worldRay, float& tHit) {

  tHit = MaxFloat;

  // iterate over shapes, collect smallest tHit
  for (auto & pShape : vShapes) {
    float t;
    if (pShape->intersect(worldRay, t)) {
      // printf("t = %f\n", t);
      if (t < tHit)
        tHit = t;
    } 
  }

  // printf("tHit = %f\n", tHit);
  // return true if some tHit value was found
  return tHit < MaxFloat;
}
