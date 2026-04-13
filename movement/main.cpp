#include <raylib.h>
#include <raymath.h>

int main()
{
  const float windowWidth  { 1920 };
  const float windowHeight { 1080 };

  InitWindow(windowWidth, windowHeight, "move");

  const float radius { 50 };
  const float speed  { 200 };
  Vector2 position   { windowWidth / 2 - radius, windowHeight / 2 - radius };
  Vector2 direction  { 0.0f, 0.0f };


  while (!WindowShouldClose())
  {
    auto dt { GetFrameTime() };

    direction = { 0.0f, 0.0f }; // reset the direction each frame

    // input

    if (IsKeyDown(KEY_D))
    {
      direction.x += 1;
    }

    if (IsKeyDown(KEY_A))
    {
      direction.x -= 1;
    }

    if (IsKeyDown(KEY_W))
    {
      direction.y -= 1;
    }

    if (IsKeyDown(KEY_S))
    {
      direction.y += 1;
    }

    // update position

    direction = Vector2Normalize(direction); // normalize direction vector for smooth diagonal movement

    position.x += direction.x * speed * dt;
    position.y += direction.y * speed * dt;

    // bound checking

    if (position.x > windowWidth - radius)
    {
      position.x = windowWidth - radius;
    }

    if (position.x < radius)
    {
      position.x = radius;
    }

    if (position.y > windowHeight - radius)
    {
      position.y = windowHeight - radius;
    }

    if (position.y < radius)
    {
      position.y = radius;
    }

    // drawing

    BeginDrawing();

      DrawCircleV(position, radius, PINK);
      ClearBackground(BLACK);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
