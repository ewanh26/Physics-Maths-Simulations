#ifndef RAYLIB_H
  #include "raylib.h"
#endif
#ifndef OBJECT_H
#define OBJECT_H

/**
 * * Force has its magnitude in
 * * the given direction
 * * stored in its x and y
 * * properties.
*/
struct Force
{
  float x;
  float y;
};

/**
 * * Simulated Object
 * contains:
 * x and y pos.
 * width and height (x and y in size).
 * velocities in x and y directions.
 * mass (theoretically in kilograms).
 * color.
 * a function which allows you to apply a
 * force to the object
*/
struct Object
{
  Vector2 pos;
  Vector2 size;
  Vector2 vel;
  float mass;
  Color color;
  void addForce(Force force, float deltatime);
};

/**
 * * Implements Newton's second law of motion
 * * F = ma (in this case a = F/m)
 * calculates acceleration then adds it
 * to the object's velocity
 * (or subtracts if acceleration is negative)
*/
void Object::addForce(Force f, float deltatime)
{
  vel.x += (f.x / mass) * deltatime;
  vel.y += (f.y / mass) * deltatime;
}
#endif