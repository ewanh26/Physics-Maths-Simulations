#include "raylib.h"
#include <math.h>
#include <vector>
#include <string>

#define SCREEN_WIDTH 1240
#define SCREEN_HEIGHT 766
#define CENTRE Vector2{ 0, 0 }
#define OFFSET_CENTRE Vector2{ SCREEN_WIDTH/2, SCREEN_HEIGHT/2 }

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Spirograph");

  float alpha = 0; // α
  float beta; // β
  const float r_1 = 100.0f; // radius of centre circle
  const float r_2 = r_1 / -2.01f; // radius of second circle (can be negative if inside of centre circle)
  const float l = r_2; // length of line (+ - makes no difference)
  float s;
  Vector2 p_1;
  Vector2 p_2;

  std::vector<Vector2> lines;
  bool pause = 0;
  bool showPattern = 1;

  Camera2D camera
  {
    .offset = OFFSET_CENTRE,
    .target = CENTRE,
    .rotation = 0.0f,
    .zoom = 1.0f
  };

  SetTargetFPS(60);

  auto update = [&]()
  {
    if (IsKeyReleased(KEY_SPACE)) pause = !pause;
    if (IsKeyReleased(KEY_P))
    {
      lines.clear();
      showPattern = !showPattern;
    }
    if (IsKeyDown(KEY_RIGHT)) camera.offset.x -= 5;
    if (IsKeyDown(KEY_LEFT)) camera.offset.x += 5;
    if (IsKeyDown(KEY_UP)) camera.offset.y += 5;
    if (IsKeyDown(KEY_DOWN)) camera.offset.y -= 5;
    if (IsKeyDown(KEY_A)) camera.rotation -= 2;
    if (IsKeyDown(KEY_D)) camera.rotation += 2;
    if (IsKeyDown(KEY_R)) 
    {
      camera.offset = OFFSET_CENTRE;
      camera.rotation = 0;
    }
    if (IsKeyDown(KEY_W)) camera.zoom += 0.05f;
    if (IsKeyDown(KEY_S)) camera.zoom -= 0.05f;

    s = alpha * r_2; // degrees (alpha / 360) * (2 * PI * r_2);
    beta = s / r_1; // degrees (360 * s) / (2 * PI * r_1);
    p_1 =
    {
      (r_1 + r_2) * cos(beta),
      (r_1 + r_2) * sin(beta)
    };
    p_2 =
    {
      p_1.x + l * cos(alpha),
      p_1.y + l * sin(alpha)
    };
    if (!pause)
    {
      lines.push_back(p_2);
      alpha += 0.2f;
    }
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(camera);
    if (!pause)
    {
      DrawCircleLines(p_1.x, p_1.y, r_2, BLUE);
      DrawCircleLines(CENTRE.x, CENTRE.y, r_1, RED);
      DrawLineV(p_1, p_2, RED);
    }
    if (showPattern)
    {
      for (size_t i = 1; i < lines.size(); i++) DrawLineV(lines[i-1], lines[i], WHITE);
    }
    EndMode2D();
    std::string FPS = "FPS: " + std::to_string(GetFPS());
    DrawText(FPS.c_str(), 5, 5, 10, GRAY);
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }

  // De-init

  CloseWindow();

  return 0;
}