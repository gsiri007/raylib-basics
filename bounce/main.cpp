#include <raylib.h>

int main()
{
  const float windowWidth  { 1920 };
  const float windowHeight { 1080 };

  InitWindow(windowWidth, windowHeight, "bounce");

  const float radius { 50 };
  Vector2 position { 100, 200 };
  Vector2 velocity { 200, 200 };

  while (!WindowShouldClose())
  {
    auto dt { GetFrameTime() };

    BeginDrawing();
      ClearBackground(BLACK);

      if (position.x > windowWidth - radius)
      {
        position.x = windowWidth - radius;
        velocity.x *= -1;
      }

      if (position.x < radius)
      {
        position.x = radius;
        velocity.x *= -1;
      }

      if (position.y > windowHeight - radius)
      {
        position.y = windowHeight - radius;
        velocity.y *= -1;
      }

      if (position.y < radius)
      {
        position.y = radius;
        velocity.y *= -1;
      }

      position.x += velocity.x * dt;
      position.y += velocity.y * dt;

      DrawCircleV(position, radius, YELLOW);
    EndDrawing();
  }

  CloseWindow();
}
