#include <raylib.h>
#include <raymath.h>

int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "oruguru");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update

    // Draw
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
