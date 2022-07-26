#include <math.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "raylib.h"
#include "object.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define g 9.80665f // Gravitational Field Strength of Earth

// Length of pendulum string
const float L = 100.0f;
// Amount of radians up at the beginning
float theta_curr = PI / 2;
// No angular velocity at the beginning
float dtheta_curr = 0;
// Air resistance factor μ affecting angular velocity
float mu = 0.01f;
// small Δt
#define delta_t GetFrameTime()*2

// Differential Equation
float get_d2theta(float theta, float dtheta)
{
  return -mu * dtheta -(g/L) * sin(theta);
}

float get_theta()
{
  float dtheta = dtheta_curr;
  float theta = theta_curr;
  float d2theta = get_d2theta(theta, dtheta);
  dtheta += d2theta * delta_t;
  theta += dtheta * delta_t;
  dtheta_curr = dtheta;
  theta_curr = theta;
  return theta;
}

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pendulum");
  
  float theta = theta_curr;
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
    theta = get_theta();
    pendulum.pos = { L * sin(theta), L * cos(theta) };
    pov.zoom += GetMouseWheelMove()*0.1f;
    pov.rotation = 0;
  };

  auto render = [&]()
  {
    ClearBackground(BLACK);
    BeginDrawing();
    BeginMode2D(pov);
    DrawCircleV(pendulum.pos, pendulum.size.x, pendulum.color);
    DrawLineEx(pendulum.pos, { 0.0f, 0.0f }, 1/pov.zoom*2, WHITE);
    DrawTexture(*chosenImg, -chosenImg->width/2, L*1.2f, WHITE);
    char theta_buffer[64];
    int ret = snprintf(theta_buffer, 64, "theta (radians): %f", theta);
    if (ret<0 || ret > 64) exit(1);
    DrawText(theta_buffer, -SCREEN_WIDTH/2 + 10, -SCREEN_HEIGHT/2 + 60, 20, WHITE);
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
