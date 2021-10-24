#ifndef RAYLIB_H
# include "raylib.h"
#endif
#ifndef ELASTICITY_H
#define ELASTICITY_H

/**
 * * Hooke's Law
*/
float Fe(float k, float e);

/**
 * Get angle using lengths of x and y differences and arctan
 * Use the magnitude (hypoteneuse, F) and angle to find Fx and Fy
*/
Vector2 getComponentsFe(Vector2 p1, Vector2 center, float k);

#endif