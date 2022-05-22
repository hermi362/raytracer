#pragma once

#include "color.h"

struct Material
{
  Color color;
  float ambient;
  float diffuse;
  float specular;
  float shininess;

  Material(Color c, float a, float d, float sp, float sh) : 
    color(c), ambient(a), diffuse(d), specular(sp), shininess(sh) {}

  Material() {
    color = Color(1.0f, 1.0f, 1.0f); 
    ambient = 0.1f;
    diffuse = 0.9f;
    specular = 0.9f;
    shininess = 20.0f;
  }
};
