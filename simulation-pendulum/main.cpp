#include "raylib.h"
#include "object.h"
#include <math.h>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define g 9.80665f // Gravitational Field Strength of Earth

// Length of pendulum string
const float L = 100.0f;
// Amount of radians up at the beginning
float theta_0 = PI / 2;
// No angular velocity at the beginning
float dtheta_0 = 0;
// Air resistance factor μ affecting angular velocity
float mu = 0.01f;
// small Δt
#define delta_t GetFrameTime()*2

// Differential Equation
float get_d2theta(float theta, float dtheta)
{
  return -mu * dtheta -(g/L) * sin(theta);
}

float get_theta(float t)
{
  float theta = theta_0;
  float dtheta = dtheta_0;
  for (float time = 0; time < t; time += delta_t)
  {
    float d2theta = get_d2theta(theta, dtheta);
    theta += dtheta * delta_t;
    dtheta += d2theta * delta_t;
  }
  return theta;
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum");

  float t = 0;
  float theta = theta_0;
  bool derivativeForm = 0;

  Texture2D ODEderivative = LoadTexture("./ODEderivative.PNG");
  Texture2D ODEdot = LoadTexture("./ODEdot.PNG");
  Texture2D* chosenImg = derivativeForm ? &ODEderivative : &ODEdot;

  Camera2D pov
  {
    { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - L/2 }, // Offset
    { 0, 0 }, // Target
    0.0f, // Rotation
    1.0f // Zoom
  };

  Object pendulum
  {
    .pos = { L * sin(theta), L * cos(theta) },
    .size = { L/10, L/10 },
    .vel = { 0.0f, 0.0f },
    .mass = 0.0f,
    .color = RED
  };

  SetTargetFPS(60);

  auto update = [&]()
  {
    if (IsKeyReleased(KEY_SPACE)) derivativeForm = !derivativeForm;

    chosenImg = derivativeForm ? &ODEderivative : &ODEdot;
    theta = get_theta(t);
    pendulum.pos = { L * sin(theta), L * cos(theta) };
    pov.zoom += GetMouseWheelMove()*0.1f;
    pov.rotation = 0;
    t += delta_t;
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(pov);
    DrawCircleV(pendulum.pos, pendulum.size.x, pendulum.color);
    DrawLineEx(pendulum.pos, { 0.0f, 0.0f }, 1/pov.zoom*2, WHITE);
    DrawTexture(*chosenImg, -chosenImg->width/2, L*1.2f, WHITE);
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