#include <raylib.h>
#include <raymath.h>

void draw_heart(Vector2 center, int radius, Color color) {
  Vector2 circles[2] = {{.x = center.x - radius, .y = center.y - radius},
                        {.x = center.x + radius, .y = center.y - radius}};
  Vector2 triangle[3] = {
      {.x = center.x + 2 * radius, .y = center.y - (radius * 0.62)},
      {.x = center.x - 2 * radius, .y = center.y - (radius * 0.62)},
      {.x = center.x, .y = center.y + radius * 1.5}};

  DrawCircle(circles[0].x, circles[0].y, radius, color);
  DrawCircle(circles[1].x, circles[1].y, radius, color);
  DrawTriangle(triangle[0], triangle[1], triangle[2], color);
  DrawRectangle(center.x - radius / 2, center.y - radius, radius, radius,
                color);
}

void draw_health(Vector2 topLeft, int totalHearts, int heartsLeft) {
  int margin = 5;
  int radius = 10; // HEART SIZE
  Vector2 center = {.x = topLeft.x + margin,
                    .y = topLeft.y + radius / 2 + margin};

  for (int i = 0; i < totalHearts; i++) {
    center.x = center.x + 4.5 * radius;
    if (i < heartsLeft) {
      draw_heart(center, radius, RED);
    } else {
      draw_heart(center, radius, GRAY);
    }
  }
}

int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "oruguru");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    Vector2 v = {.x = 100, .y = 100};
    // Draw
    BeginDrawing();
    {
      ClearBackground(DARKGRAY);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);
      draw_health(v, 3, 3);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
