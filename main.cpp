#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include "tuple.h"
#include "color.h"
#include "tests.h"
#include "canvas.h"
#include "matrix.h"



/* struct Projectile {
  Point position;
  Vector velocity;
};
struct Environment {
  Vector gravity;
  Vector wind;
};
Projectile tick(Environment env, Projectile proj) {
  Projectile p1;
  p1.position = proj.position + proj.velocity;
  p1.velocity = proj.velocity + env.gravity + env.wind;
  return p1;
}

void playProjectileGame() {
  Projectile p;
  p.position = Point(0, 30, 0);
  p.velocity = Vector(8, 10, 0);
  Environment e;
  e.gravity = Vector(0, -1, 0);
  e.wind    = Vector(-0.2, 0, 0);

  Canvas can(160, 100);
  auto i = 30;
  while(i-- > 0)
  {
    p = tick(e, p);
    printf("(%2.3f,%2.3f)  [%2.3f, %2.3f]\n", p.position.x, p.position.y, p.velocity.x, p.velocity.y);
    const int x = (int)p.position.x;
    const int y = (int)p.position.y;
    if (x > 0 && x < can.width() && y > 0 && y < can.height()) {
      can.writePixel(x, can.height()-y, Color(1,0,0));
    }
  }

  std::ofstream ostrm("projectile.ppm");
  ostrm << can.toPPM();

} */


int main() {

  runTests();


  // nothing
  // playProjectileGame();  
  return 0;
}

