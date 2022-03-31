#include "raylib.h"
#include "object.h"
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define DELTATIME GetFrameTime()
#define g 9.98f

// ! NOTE: JUMPING IS KINDA BUGGED RN

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Weight");

  Object object
  {
    Vector2{ SCREEN_WIDTH/2 - object.size.x/2, 10 },
    Vector2{ 40, 40 },
    Vector2{ 0, 0 },
    1,
    RED
  };

  auto update = [&]()
  {
    if (IsKeyReleased(KEY_SPACE))
    {
      object.addForce(Force{ 0, -1000 }, DELTATIME);
      object.pos.y += object.vel.y;
    }

    if (object.pos.y + object.vel.y + object.size.y < SCREEN_HEIGHT)
    {
      object.addForce(Force{ 0, (object.mass * g) * 0.1f }, DELTATIME);
      object.pos.y += object.vel.y;
    }
  };

  auto render = [&]()
  {
    ClearBackground(RAYWHITE);
    BeginDrawing();
    DrawRectangleV(object.pos, object.size, object.color);
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }

  CloseWindow(); 

}