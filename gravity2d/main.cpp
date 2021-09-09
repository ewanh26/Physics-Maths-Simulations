#include "raylib.h"
#include <math.h>
#include <iostream>
#include <iomanip>

// * Gravitational constant
#define G 6.67f * 10e-11

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

// ! NOTE: THIS IS CURRENTLY A WORK IN PROGRESS AND NOT PROPERLY FUNCTIONAL/CORRECT

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
 * x and y pos.
 * width and height (x and y in size).
 * velocities in x and y directions.
 * mass (theoretically in kilograms).
 * a function which allows you to apply a
 * force to the object
*/
struct SimObject
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
 * Get angle using lengths of x and y differences and tangent-1
 * Use the magnitude (hypoteneuse, F) and angle to find Fx and Fy
 * TODO: NEGATIVE COMPONENTS
 * TODO: FIX THIS WHAT IS GOING ON
*/
Vector2 getPerpendicularMagnitudes(Vector2 pos1, Vector2 pos2, float fTotalMagnitude)
{
  float theta = atan((pos1.y - pos2.y) / (pos1.x - pos2.x)) * 180/PI;
  float Fx = (cos(theta) * 180/PI) * (pos1.x - pos2.x < 0 ? fTotalMagnitude : -fTotalMagnitude);
  float Fy = (sin(theta) * 180/PI) * (pos1.y - pos2.y < 0 ? -fTotalMagnitude : fTotalMagnitude);
  std::cout << "theta: " << theta << " ";
  std::cout << "Fx: " << Fx << " Fy: " << Fy;
  return Vector2{ Fx, Fy };
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

void update(SimObject& square, SimObject centreGrav, Camera2D& pov)
{
  pov.zoom += (float)(GetMouseWheelMove()*0.01f);
  pov.target = centreGrav.pos;

  square.addForce
  (
    Force
    { 
      getPerpendicularMagnitudes
      (
        square.pos,
        centreGrav.pos,
        gravity(square.pos, centreGrav.pos, square.mass, centreGrav.mass)
      )
    },
    GetFrameTime()
  );

  square.pos.x += square.vel.x;
  square.pos.y += square.vel.y;

  std::cout << "xVel: "<< std::setprecision(6) << (float)square.vel.x << " yVel: " << (float)square.vel.y << "\n";
}

void render(SimObject square, SimObject centreGrav, Camera2D pov)
{
  ClearBackground(RAYWHITE);
  BeginDrawing();
  BeginMode2D(pov);
  DrawCircleV(centreGrav.pos, centreGrav.size.x, centreGrav.color);
  DrawCircleV(square.pos, square.size.x, square.color);
  EndMode2D();
  EndDrawing();
}

int main()
{
  // Initialization
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "window lol");

  SimObject square
  {
    Vector2{ 0.0f, 500.0f },
    Vector2{ 40, 40 },
    Vector2{ 0.0f, 0.0f },
    10.0f,
    RED
  };

  SimObject centreGrav
  {
    Vector2{ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f },
    Vector2{ 50.0f, 50.0f },
    Vector2{ 0.0f, 0.0f },
    5'972'900'000'000.0f,
    BLACK
  };

  Camera2D pov
  {
    { SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f }, // Offset
    centreGrav.pos,
    0.0f, // Rotation
    1.0f // Zoom
  };

  SetTargetFPS(60);               // 60 frames-per-second

  // Main loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
  {
    update(square, centreGrav, pov);

    render(square, centreGrav, pov);
  }

  // De-Initialization
  CloseWindow();        // Close window and OpenGL context

  return 0;
}