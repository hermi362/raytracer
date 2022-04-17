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


void drawClock() {
  std::cout << "Drawing clock..." << std::endl;
  Canvas can(100, 100);
  // draw a point at the center of the clock
  can.writePixel(can.width()/2, can.width()/2, Color(1,1,1));

  Point hourHand(40,0,0);
  Matrix rotOneHour = getRotationZ(PI/6);
  for (int i=0 ; i<12 ; i++) {
    hourHand = rotOneHour * hourHand;
    can.writePixel(can.width()/2 + hourHand.x, can.height()/2 + hourHand.y, Color(1,0,0));
  }

  std::ofstream ostrm("clock.ppm");
  ostrm << can.toPPM();
  std::cout << "Finished." << std::endl;
}


int main() {

  runTests();


  // nothing
  // playProjectileGame();
  drawClock();
  return 0;
}

