#ifndef _MATH_H
# include <math.h>
#endif
#ifndef RAYLIB_H
# include "raylib.h"
#endif
#ifndef MATHEXT_H
#define MATHEXT_H

/**
 * * Pythagoras' theorem to find distance
 * * between two points.
 * * a^2 + b^2 = c^2.
 * a being the difference of their x values.
 * b being the difference of their y values.
 * c^2 being the distance between the points
 * (the hypoteneuse).
*/
inline float distance(Vector2 p1, Vector2 p2)
{
  return hypot
  (
    p1.x - p2.x,
    p1.y - p2.y
  );
}

#endif