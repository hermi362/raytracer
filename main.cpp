#include <iostream>
#include <fstream>
#include "tests.h"
#include "film.h"
#include "point.h"
#include "light.h"
#include "sphere.h"
#include "ray.h"
#include "intersections.h"



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

  int film_pixels = 200;
  Film film(film_pixels, film_pixels);

  Point ray_origin(0,0,-10.f);
  float wall_z = 10.f;
  float wall_size = 7.f;
  float pixel_size = wall_size / film_pixels;
  float half = wall_size / 2;

  PointLight light(Point(5,10,-10), Color(0.8, 0.4, 0.0));

  Sphere sphere;
  // sphere.material.ambient = 0.1f;
  // sphere.material.diffuse = 0.9;
  // sphere.material.specular = 0.3;
  // sphere.setTransform(getTranslation(0.5,0,0));
  // sphere.setTransform(getScaling(1, 0.5, 1));
  // sphere.setTransform(getRotationZ(PI/4) * getScaling(1, 0.2, 1) * getTranslation(0.8, 0, 0) );
  // sphere.setTransform(getShear(1,0,0,0,0,0) * getScaling( .5, 1, 1) );
  // sphere.setTransform(getRotationX(PI/8) * getScaling(1.5, 0.2, 1) );

  for (int y=0 ; y<film_pixels ; y++) {
    float world_y = half - pixel_size * y;

    for (int x=0 ; x<film_pixels ; x++) {
      float world_x = -half + pixel_size * x;

      // describe the point on wall that ray will target
      Point position(world_x, world_y, wall_z);

      Vector ray_direction = Vector(position - ray_origin).normalize();
      Ray r(ray_origin, ray_direction);
      float thit;
      bool hit;
      hit = intersect(r, &sphere, thit);

      if (hit) {
        Point wrldIntersect = sphere.transform * r.getPosition(thit);
        Vector eyev = (ray_origin - wrldIntersect).normalize();
        Vector normal = sphere.getNormalAt(wrldIntersect);
        Color shade = lighting(sphere.material, light, wrldIntersect, eyev, normal);
        film.writePixel(x, y, shade);
      }

    } // x++

  if (y%50==0) std::cout << "line " << y << std::endl;
  } // y++

  std::ofstream ostrm("sphere.ppm");
  ostrm << film.toPPM();
  std::cout << "Finished." << std::endl;

}