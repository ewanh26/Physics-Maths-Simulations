#ifndef GRAVITY_H
#define GRAVITY_H
#ifndef RAYLIB_H
#include "raylib.h"
#endif

/**
 * Get angle using lengths of x and y differences and arctan
 * Use the magnitude (hypoteneuse, F) and angle to find Fx and Fy
*/
Vector2 getComponentsFg(Vector2 pos1, Vector2 pos2, float fTotalMagnitude);

/**
 * * Implements Newton's law of universal gravitation
 * * Fg = G * (m1 * m2 / r^2)
 * G = Gravitational constant
 * m[x] = mass of object x
 * r = distance between objects
*/
float gravity(Vector2 pos1, Vector2 pos2, float m1, float m2);

#endif
