#include "raylib.h"
#include <math.h>
#include <iostream>
#include <iomanip>

// * Gravitational constant
#define G 6.67f * 10e-11

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

/**
 * * Force has its magnitude in
 * * the given direction
 * * stored in its x and y
 * * properties.
*/
struct Force
{
  Vector2 magnitudeInDir;
};

/**
 * * Simulated Object
 * contains:
 * x and y position.
 * width and height (x and y in size).
 * velocities in x and y directions.
 * mass (theoretically in kilograms).
 * a function which allows you to apply a
 * force to the object
*/
struct SimObject
{
  Vector2 position;
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
void SimObject::addForce(Force f, float deltatime)
{
  vel.x += (f.magnitudeInDir.x / mass) * deltatime;
  vel.y += (f.magnitudeInDir.y / mass) * deltatime;
}

/**
 * * Pythagoras' theorem to find distance
 * * between two points.
 * * a^2 + b^2 = c^2.
 * a being the difference of their x values.
 * b being the difference of their y values.
 * c^2 being the distance between the points
 * (the hypoteneuse).
*/
float distance(Vector2 p1, Vector2 p2)
{
  return sqrt
  (
    pow(p1.x - p2.x, 2)
    + pow(p1.y - p2.y, 2)
  );
}

/**
 * * Implements Newton's law of universal gravitation
 * * Fg = G * (m1 * m2 / r^2)
 * G = Gravitational constant
 * m[x] = mass of object x
 * r = distance between objects
*/
float gravity(Vector2 pos1, Vector2 pos2, float m1, float m2)
{
  float dist = distance(pos1, pos2);
  return G * ((m1 * m2) / (dist*dist));
}

void update(SimObject &square, SimObject ground)
{
  float* x = &square.position.x;
  float* y = &square.position.y;
  
  if (*x > 0) *x += square.vel.x;
  if (*y <= SCREEN_HEIGHT - 50.0f - square.size.y - 8.5f) *y += square.vel.y;

  square.addForce
  (
    Force{ Vector2{ 0, gravity(square.position, ground.position, square.mass, ground.mass) } },
    GetFrameTime()
  );
  std::cout << "y: "<< std::setprecision(6) << (float)square.position.y << " x: " << (float)square.position.y << "\n";
}

void render(SimObject square, SimObject ground)
{
  ClearBackground(RAYWHITE);
  BeginDrawing();
  DrawRectangleV(square.position, square.size, square.color);
  DrawRectangleLines(square.position.x, square.position.y, square.size.x, square.size.y, GREEN);
  DrawRectangleV(ground.position, ground.size, ground.color);
  EndDrawing();
}

int main()
{
  // Initialization
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window lol");

  SimObject square =
  {
    Vector2{ SCREEN_WIDTH/2.0f - 20.5f, SCREEN_HEIGHT/2.0f - 20.5f - 100.0f },
    Vector2{ 40, 40 },
    Vector2{ 0.0f, 0.0f },
    10.0f,
    RED
  };

  SimObject ground =
  {
    Vector2{ 0, SCREEN_HEIGHT - 50.0f },
    Vector2{ SCREEN_WIDTH, 50.0f },
    Vector2{ 0.0f, 0.0f },
    5'972'200'000'000'000.0f,
    BLACK
  };

  SetTargetFPS(60);               // 60 frames-per-second

  // Main loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    update(square, ground);

    render(square, ground);
  }

  // De-Initialization
  CloseWindow();        // Close window and OpenGL context

  return 0;
}