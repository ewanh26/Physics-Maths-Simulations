#include "raylib.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <math.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

// "The golden ratio" φ = 1.61803...
#define PHI ((1 + sqrt(5)) / 2)
#define GOLDEN_ANGLE(n) 360 - 360/(PHI+n)

int main(int argc, char** argv)
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The golden ratio");
  bool toggle = false;

  float theta = 0; // θ
  float r = 1; // radius
  std::vector<Vector2> points; // stores all points
  int n = argc == 1 ? 0 : argc == 2 ? 1 : argc == 3 ? -1 : 0;

  Camera2D camera
  {
    { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 },
    { 0, 0 },
    0,
    1.0f
  };

  SetTargetFPS(60);

  auto update = [&]()
  {
    camera.zoom += GetMouseWheelMove()*0.1f;
    if (IsKeyPressed(KEY_SPACE)) toggle = !toggle;
    if (toggle)
    {
      r += .025f;
      theta += GOLDEN_ANGLE(n);

      float dx = sin(theta) * r;
      float dy = cos(theta) * r;

      points.push_back(Vector2{ dx, dy });
    }
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera);
    for (size_t i = 0; i < points.size(); i++)
    {
      DrawCircleV(points[i], .25f, RAYWHITE);
      // DrawLineV({ 0, 0 }, points[i], RED);
    }
    EndMode2D();
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }

  // Deinit
  
  CloseWindow();

  return 0;
}