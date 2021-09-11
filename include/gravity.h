#ifndef GRAVITY_H
#define GRAVITY_H
#ifndef RAYLIB_H
#include "raylib.h"
#endif

/**
 * Get angle using lengths of x and y differences and tangent-1
 * Use the magnitude (hypoteneuse, F) and angle to find Fx and Fy
*/
Vector2 getPerpendicularMagnitudes(Vector2 pos1, Vector2 pos2, float fTotalMagnitude);

/**
 * * Implements Newton's law of universal gravitation
 * * Fg = G * (m1 * m2 / r^2)
 * G = Gravitational constant
 * m[x] = mass of object x
 * r = distance between objects
*/
float gravity(Vector2 pos1, Vector2 pos2, float m1, float m2);


/**
 * * Pythagoras' theorem to find distance
 * * between two points.
 * * a^2 + b^2 = c^2.
 * a being the difference of their x values.
 * b being the difference of their y values.
 * c^2 being the distance between the points
 * (the hypoteneuse).
*/
float distance(Vector2 p1, Vector2 p2);
#endif
