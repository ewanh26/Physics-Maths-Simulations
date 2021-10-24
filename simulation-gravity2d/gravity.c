#ifndef RAYLIB_H
  #include "raylib.h"
#endif
#ifndef SCREEN_WIDTH
  #define SCREEN_WIDTH 800
#endif
#ifndef SCREEN_HEIGHT
  #define SCREEN_HEIGHT 450
#endif
#ifndef _MATH_H
  #include <math.h>
#endif
#ifndef MATHEXT_H
  #include "math_ext.h"
#endif
// * Gravitational constant
#define G 6.67f * 10e-11

Vector2 getComponentsFg(Vector2 p1, Vector2 p2, float fTotalMagnitude)
{
  float theta = abs(atan((p1.y - p2.y) / (p1.x - p2.x)) * 180/PI);
  float Fx = (abs(cos(theta)) * 180/PI) * fTotalMagnitude;
  float Fy = (abs(sin(theta)) * 180/PI) * fTotalMagnitude;
  if (p1.x <= 0 && p1.y <= 0) return (Vector2){ Fx, Fy }; // Top Left
  if (p1.x >= 0 && p1.y <= 0) return (Vector2){ -Fx, Fy }; // Top Right
  if (p1.x >= 0 && p1.y >= 0) return (Vector2){ -Fx, -Fy }; // Bottom Right
  if (p1.x <= 0 && p1.y >= 0) return (Vector2){ Fx, -Fy }; // Bottom Left
  
  return (Vector2){ 0, 0 };
}

float gravity(Vector2 pos1, Vector2 pos2, float m1, float m2)
{
  float dist = distance(pos1, pos2);
  return G * ((m1 * m2) / (dist*dist));
}