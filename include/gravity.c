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
// * Gravitational constant
#define G 6.67f * 10e-11

float distance(Vector2 p1, Vector2 p2)
{
  return sqrt
  (
    pow(p1.x - p2.x, 2)
    + pow(p1.y - p2.y, 2)
  );
}

Vector2 getPerpendicularMagnitudes(Vector2 pos1, Vector2 pos2, float fTotalMagnitude)
{
  float theta = abs(atan((pos1.y - pos2.y) / (pos1.x - pos2.x)) * 180/PI);
  float Fx = (abs(cos(theta)) * 180/PI) * fTotalMagnitude;
  float Fy = (abs(sin(theta)) * 180/PI) * fTotalMagnitude;
  if (pos1.x <= SCREEN_WIDTH/2 && pos1.y <= SCREEN_HEIGHT/2) return (Vector2){ Fx, Fy }; // Top Left
  if (pos1.x >= SCREEN_WIDTH/2 && pos1.y <= SCREEN_HEIGHT/2) return (Vector2){ -Fx, Fy }; // Top Right
  if (pos1.x >= SCREEN_WIDTH/2 && pos1.y >= SCREEN_HEIGHT/2) return (Vector2){ -Fx, -Fy }; // Bottom Right
  if (pos1.x <= SCREEN_WIDTH/2 && pos1.y >= SCREEN_HEIGHT/2) return (Vector2){ Fx, -Fy }; // Bottom Left
  
  return (Vector2){ 0, 0 };
}

float gravity(Vector2 pos1, Vector2 pos2, float m1, float m2)
{
  float dist = distance(pos1, pos2);
  return G * ((m1 * m2) / (dist*dist));
}