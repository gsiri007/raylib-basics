#include <raylib.h>

int main()
{
  const int windowWidth  { 900 };
  const int windowHeight { 800 };
  InitWindow(windowWidth, windowHeight, "Audio");

  InitAudioDevice();

  // music are streamed from the disk
  // music are for long running tracks
  auto bgMusic { LoadMusicStream("./assets/Gravity-Edge.mp3") };
  PlayMusicStream(bgMusic);

  while (!WindowShouldClose())
  {

    UpdateMusicStream(bgMusic);

    BeginDrawing();
      ClearBackground(BLACK);
    EndDrawing();

  }

  UnloadMusicStream(bgMusic);
  CloseAudioDevice();
  CloseWindow();
  return 0;
}
