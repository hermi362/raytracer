#include "ray.h"

// Compute the position of this ray at the distance t along the ray
Point Ray::getPosition(float t) {
  return origin + (t * direction);
}

// return a new ray after applying transformation
Ray Ray::transform(const Matrix& m) {
  Ray ret;

  ret.origin = m * origin;
  ret.direction = m * direction;
  
  return ret;
}

Vector reflect(const Vector& in, const Vector& normal) {
  return in - normal * 2.0f * in.dot(normal);
}

Color lighting(Material material, PointLight light, Point point, Vector eyev, Vector normalv) {
  Color ambient, diffuse, specular;
  const static Color BLACK = Color(0,0,0);

  // combine the surface color with the light color
  Color effectiveColor = material.color * light.intensity;

  // find the direction to the light source
  Vector lightv = (light.position - point).normalize();

  // compute the abient contribution
  ambient = effectiveColor * material.ambient;

  float lightDotNormal = lightv.dot(normalv);
  if (lightDotNormal < 0) {
    diffuse = BLACK;
    specular = BLACK;
  } else {
    // compute diffuse contribution
    diffuse = effectiveColor * material.diffuse * lightDotNormal;

    Vector reflectv = reflect(-lightv, normalv);
    float reflectDotEye = reflectv.dot(eyev);
    if (reflectDotEye > 0) // if light is reflecting towards eye
    {
      // compute specular contribution
      float factor = pow(reflectDotEye, material.shininess);
      specular = light.intensity * material.specular * factor;
    }
  }

  return ambient + diffuse + specular;
}