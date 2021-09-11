#include "raylib.h"
#include "object.h"
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define DELTATIME GetFrameTime()

// ! NOTE: THIS MOSTLY WORKS (SHOWS THE MAIN GIST)

// * Gravitational field strength of Earth
#define g 9.81f

/**
 * * Gravitational potential energy
 * * Ep = m * g * h
*/
float Ep(Object object)
{
  return object.mass * g * (SCREEN_HEIGHT - object.pos.y - object.size.x);
}

/**
 * * Velocity of given object
 * * Ek = m/2 * v^2, or in this case
 * * v^2 = Ek / m/2
*/
float velocity(Object object)
{
  return Ep(object) / (object.mass / 2) * DELTATIME;
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Gravitational Potential Energy");

  Object object
  {
    Vector2{ SCREEN_WIDTH/2, 100.0f },
    Vector2{ 5.0f, 5.0f },
    Vector2{ 0, 0.3f },
    10.0f,
    RED
  };

  SetTargetFPS(60);

  auto update = [&]()
  {
    Force f = Force{ 0, object.mass / (velocity(object) - object.vel.y) };
    object.addForce(f, DELTATIME);

    if (int dest = object.pos.x + object.vel.x + object.size.x; dest < SCREEN_WIDTH && dest > 0)
    {
      object.pos.x += object.vel.x;
    }
    if (int dest = object.pos.y + object.vel.y + object.size.x; dest < SCREEN_HEIGHT && dest > 0)
    {
      object.pos.y += object.vel.y;
      std::cout << "yVel: " << object.vel.y << "\n";
    } else CloseWindow();
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    DrawCircleV(object.pos, object.size.x, object.color);
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }
  
  CloseWindow();
}