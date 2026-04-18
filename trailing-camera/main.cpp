#include <array>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <random>

class Circle
{
public:
  Vector2  position;
  float    radius;
  Color    color;
};

class Player : public Circle
{
public:
  Vector2 direction;
  float   speed;
};

int main()
{
  const int windowWidth        { 1920 };
  const int windowHeight       { 1080 };
  const float halfWindowWidth  { windowWidth  / 2.0f };
  const float halfWindowHeight { windowHeight / 2.0f };
  InitWindow(windowWidth, windowHeight, "Camera");

  std::array<Color, 4>                  colors { RED, GREEN, BLUE, YELLOW };
  std::vector<std::shared_ptr<Circle>>  circles;
  std::random_device                    randomDevice;

  for (int i = 0; i < 400; ++i)
  {
    std::mt19937 gen(randomDevice());
    std::uniform_real_distribution<>  worldDistribution(-2000, 4000);
    std::uniform_real_distribution<>  radiusDistribution(25, 100);
    std::uniform_int_distribution<>   colorDistribution(0, colors.size() - 1);

    auto circle = std::make_shared<Circle>(Circle {
          Vector2 { (float) worldDistribution(gen), (float) worldDistribution(gen) },
          (float) radiusDistribution(gen),
          colors[colorDistribution(gen)]
    });

    circles.push_back(circle);
  }

  Player player {
    Vector2 { halfWindowWidth, halfWindowHeight },
    25,
    WHITE,
    Vector2 { 0, 0 },
    200
  };

  Camera2D camera;
  camera.zoom = 1;
  camera.target = player.position;
  camera.offset = Vector2 { halfWindowWidth, halfWindowHeight };

  while (!WindowShouldClose())
  {
    player.direction = Vector2 { 0, 0 };

    //get delta time
    const auto dt { GetFrameTime() };

    // user input
    if (IsKeyDown(KEY_W))
    {
      player.direction.y = -1;
    }

    if (IsKeyDown(KEY_S))
    {
      player.direction.y = 1;
    }

    if (IsKeyDown(KEY_D))
    {
      player.direction.x = 1;
    }

    if (IsKeyDown(KEY_A))
    {
      player.direction.x = -1;
    }

    // update player position
    player.direction = Vector2Normalize(player.direction);

    player.position.x += player.direction.x * player.speed * dt;
    player.position.y += player.direction.y * player.speed * dt;

    camera.target = player.position;

    // drawing
    BeginDrawing();
    BeginMode2D(camera);
      ClearBackground(BLACK);
      for ( auto circle : circles)
      {
        DrawCircleV(circle->position, circle->radius, circle->color);
      }
      DrawCircleV(player.position, player.radius, player.color);
    EndMode2D();
    EndDrawing();

  }

  CloseWindow();
  return 0;
}
