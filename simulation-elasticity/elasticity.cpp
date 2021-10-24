#ifndef ELASTICITY_H
# include "elasticity.h"
#endif
#ifndef RAYLIB_H
# include "raylib.h"
#endif
#ifndef _MATH_H
# include <math.h>
#endif
#ifndef MATH_EXT_H
# include "math_ext.h"
#endif

float Fe(float k, float e)
{
  return k * e;
}

Vector2 getComponentsFe(Vector2 p1, Vector2 center, float k)
{
  float dx = p1.x - center.x;
  float dy = p1.y - center.y;
  float e = distance(p1, center);
  float theta = atan(dy/dx);
  float F = Fe(k, e);
  float Fx = cos(theta) * F;
  float Fy = sin(theta) * F;
  Fx = p1.x > 0 ? Fx > 0 ? -Fx : Fx : Fx < 0 ? -Fx : Fx;
  Fy = p1.y > 0 ? Fy > 0 ? -Fy : Fy : Fy < 0 ? -Fy : Fy;
  return (Vector2){ Fx, Fy };
}
