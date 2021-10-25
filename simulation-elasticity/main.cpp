#include "raylib.h"
#include "object.h"
#include <math.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include "elasticity.h"
#include "math_ext.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define CENTRE Vector2{ 0, 0 }
#define DELTATIME GetFrameTime()

Force getFullFe(float k, Object obj)
{
  Vector2 F = getComponentsFe
  (
    obj.pos,
    CENTRE,
    k
  );

  return Force
  {
    F.x * 0.1f,
    F.y * 0.1f
  };
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hooke's Law");

  float k = 5; // Spring Constant k (N/m)
  bool toggle = 0;

  Object obj
  {
    .pos = { 0, 100 },
    .size = { 10, 10 },
    .vel = { 0, 0 },
    .mass = 10,
    .color = RED
  };

  Camera2D pov
  {
    .offset = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 },
    .target = CENTRE,
    .rotation = 0,
    .zoom = 1.0f,
  };

  SetTargetFPS(60);

  auto update = [&]()
  {
    if (!toggle)
    {
      obj.pos.x = GetMousePosition().x - SCREEN_WIDTH/2;
      obj.pos.y = GetMousePosition().y - SCREEN_HEIGHT/2;
      if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) toggle = 1;
    } else 
    {
      obj.addForce(getFullFe(k, obj), DELTATIME);

      if (IsKeyReleased(KEY_UP)) obj.addForce({ 0, -1000 }, DELTATIME);      
      if (IsKeyReleased(KEY_DOWN)) obj.addForce({ 0, 1000 }, DELTATIME);      
      if (IsKeyReleased(KEY_RIGHT)) obj.addForce({ 1000, 0 }, DELTATIME);      
      if (IsKeyReleased(KEY_LEFT)) obj.addForce({ -1000, 0 }, DELTATIME);      

      obj.pos.x += obj.vel.x;
      obj.pos.y += obj.vel.y;
    }

    // pov.zoom = GetMouseWheelMove()*0.1f;
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(pov);
    DrawCircleV(obj.pos, obj.size.x, obj.color);
    DrawLineV({ -999, 0 }, { 999, 0 }, GREEN);
    DrawLineV({ 0, -999 }, { 0, 999 }, GREEN);
    DrawLineV(CENTRE, obj.pos, RED);
    std::ostringstream oss;
    oss << "x: " << obj.pos.x << " y: " << obj.pos.y;
    DrawText(oss.str().c_str(), -SCREEN_WIDTH/2 + 10, -SCREEN_HEIGHT/2 + 10, 10, RAYWHITE);
    EndMode2D();
    EndDrawing();
  };

  while (!WindowShouldClose())
  {
    update();

    render();
  }
  
  // De-Init

  CloseWindow();

  return 0;
}