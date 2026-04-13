#include <memory>
#include <raylib.h>

int main()
{
  const float windowWidth  { 1920 };
  const float windowHeight { 1080 };

  InitWindow(windowWidth, windowHeight, "collision-overlap");

  Rectangle recOne { 100, 100, 200, 400 };
  const Rectangle recTwo { 500, 250, 200, 400 };

  while (!WindowShouldClose())
  {
    recOne.x = GetMousePosition().x;
    recOne.y = GetMousePosition().y;

    std::unique_ptr<Rectangle> overlapRec { nullptr };
    if (CheckCollisionRecs(recOne, recTwo))
    {
      overlapRec  = std::make_unique<Rectangle>(GetCollisionRec(recOne, recTwo));
    }

    BeginDrawing();

      ClearBackground(BLACK);

      DrawRectangleRec(recOne, GREEN);
      DrawRectangleRec(recTwo, WHITE);

      if (overlapRec)
      {
        DrawRectangleRec(*overlapRec, RED);
      }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
