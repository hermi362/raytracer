#include <iostream>
#include <fstream>
#include "tests.h"
#include "film.h"
#include "point.h"
#include "light.h"
#include "sphere.h"
#include "ray.h"
#include "scene.h"



int main() {

  runTests();
  // playProjectileGame();
  // drawClock();
  rayTraceSphere();

  return 0;
}

// ray-trace a sphere against a square film using hit/nonhit only.
// This should draw a solid circle on film.
void rayTraceSphere() {
  std::cout << "Rendering sphere..." << std::endl;

  int film_pixels = 400;
  Film film(film_pixels, film_pixels);

  Point ray_origin(0,0,-10.f);
  float wall_z = 10.f;
  float wall_size = 7.f;
  float pixel_size = wall_size / film_pixels;
  float half = wall_size / 2;

  PointLight light(Point(5,10,-10), Color(0.8, 0.4, 0.0));

  Sphere aRealSphere;
  Shape& myShape = aRealSphere;
  myShape.material.ambient = 0.1f;
  myShape.material.diffuse = 0.9;
  myShape.material.specular = 0.3;
  // myShape.setTransform(getTranslation(0.5,0,0));
  // myShape.setTransform(getScaling(1.4, 0.5, 1.3));
  // myShape.setTransform(getRotationZ(PI/4) * getScaling(1, 0.2, 1) * getTranslation(0.8, 0, 0) );
  // myShape.setTransform(getShear(1,0,0,0,0,0) * getScaling( .5, 1, 1) );
  // myShape.setTransform(getRotationX(PI/8) * getScaling(1.5, 0.2, 1) );

  for (int y=0 ; y<film_pixels ; y++) {
    float world_y = half - pixel_size * y;

    for (int x=0 ; x<film_pixels ; x++) {
      float world_x = -half + pixel_size * x;

      // describe the point on wall that ray will target
      Point position(world_x, world_y, wall_z);

      Vector ray_direction = Vector(position - ray_origin).normalize();
      Ray r(ray_origin, ray_direction);
      float tHit;
      bool hit;
      hit = myShape.intersect(r, tHit);

      if (hit) {
        Point wrldIntersect = myShape.objectToWorld * r.getPosition(tHit);
        Vector eyev = (ray_origin - wrldIntersect).normalize();
        Vector normal = myShape.getNormalAt(wrldIntersect);
        Color shade = lighting(myShape.material, light, wrldIntersect, eyev, normal);
        film.writePixel(x, y, shade);
      }

    } // x++

  //if (y%50==0) std::cout << "line " << y << std::endl;
  } // y++

  std::ofstream ostrm("sphere.ppm");
  ostrm << film.toPPM();
  std::cout << "Finished." << std::endl;

}
