#include "raylib.h"
#include "object.h"
#include "gravity.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include <vector>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

void addGravity(Object& object, Object centreGrav)
{
  Vector2 perpendicularMagnitude = getComponentsFg
  (
    object.pos,
    centreGrav.pos,
    gravity(object.pos, centreGrav.pos, object.mass, centreGrav.mass)
  );

  object.addForce
  (
    Force
    {
      perpendicularMagnitude.x,
      perpendicularMagnitude.y
    },
    GetFrameTime()
  );
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Newtonian gravity in space");

  std::vector<Vector2> lines;
  bool linetoggle = 0;

  Object object
  {
    Vector2{ -750.0f, 400.0f },
    Vector2{ 40, 40 },
    Vector2{ 0.0f, 0.0f },
    10.0f,
    RED
  };

  Object centreGrav
  {
    Vector2{ 0, 0 },
    Vector2{ 50.0f, 50.0f },
    Vector2{ 0.0f, 0.0f },
    5'972'900'000'000.0f,
    YELLOW
  };

  Camera2D pov
  {
    { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 }, // Offset
    centreGrav.pos,
    0.0f, // Rotation
    0.4f // Zoom
  };

  SetTargetFPS(60);

  auto update = [&, centreGrav]()
  {
    if (IsKeyReleased(KEY_UP)) object.addForce(Force{ 0, -1'000.0f }, GetFrameTime());
    if (IsKeyReleased(KEY_DOWN)) object.addForce(Force{ 0, 1'000.0f }, GetFrameTime());
    if (IsKeyReleased(KEY_RIGHT)) object.addForce(Force{ 1'000, 0.0f }, GetFrameTime());
    if (IsKeyReleased(KEY_LEFT)) object.addForce(Force{ -1'000.0, 0.0f }, GetFrameTime());
    if (IsKeyReleased(KEY_SPACE))
    {
      linetoggle = !linetoggle;
      lines.clear();
    }

    pov.zoom += (float)(GetMouseWheelMove()*0.02f);
    pov.target = centreGrav.pos;

    addGravity(object, centreGrav);

    object.pos.x += object.vel.x;
    object.pos.y += object.vel.y;
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(pov);
    DrawCircleV(centreGrav.pos, centreGrav.size.x, centreGrav.color);
    DrawCircleV(object.pos, object.size.x, object.color);
    // DrawLineV(object.pos, centreGrav.pos, BLUE);
    // DrawLineV(object.pos, Vector2{ object.pos.x, centreGrav.pos.y }, GREEN);
    // DrawLineV(centreGrav.pos, Vector2{ object.pos.x, centreGrav.pos.y }, GREEN); // Trigonometry demonstration
    if (linetoggle)
    {
      lines.push_back(object.pos);
      for (size_t i = 1; i < lines.size(); i++)
      {
        DrawLineV(lines[i-1], lines[i], RAYWHITE);
      }
    }
    EndMode2D();
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }

  CloseWindow(); 

  return 0;
}