#include "sphere.h"
#include "ray.h"

Vector Sphere::getNormalAt(const Point& worldp) const {
    Point objectp = worldToObject * worldp;
    Vector objectn = (objectp - Point(0,0,0));
    Vector worldn = worldToObject.transpose() * objectn;        
    return worldn.normalize();
}

bool Sphere::intersect(const Ray& worldRay, float& tHit) const {

  // transform ray to object coordinate system
  Ray r = worldRay.transform(worldToObject);

  // get vector from sphere centre to ray origin
  // (sphere is centered at 0,0,0)
  Vector vSphereToRay = r.getOrigin() /* - Point(0,0,0)*/;

  float a = r.getDirection().dot(r.getDirection());
  float b = 2 * r.getDirection().dot(vSphereToRay);
  float c = vSphereToRay.dot(vSphereToRay) - 1;
  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) // no intersections found
    return false;


  // float t1 = (-b - sqrt(discriminant)) / (2*a);
  // float t2 = (-b + sqrt(discriminant)) / (2*a);
  // optimized version of the above calculations for t1, t2:
  float root_disc_over_a = sqrt(discriminant) / a;
  float t1 = -0.5 * (b/a + root_disc_over_a);
  float t2 = t1 + root_disc_over_a;

  // ignore negative values
  if (t1<0 && t2<0)
    return false;

  if (t1<0 && t2>=0)
    tHit = t2;
  else if (t1>=0 && t2<0)
    tHit = t1;
  else
    tHit = min(t1, t2);

  return true;

}
