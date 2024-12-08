#include "oruguru.h"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

/* PROTOTYPES */
void draw_inputs(int input_flags);
void get_inputs(int *input_flags);

/* FUNCTIONS */
int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  int input_flags;

  InitWindow(screenWidth, screenHeight, "oruguru");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    get_inputs(&input_flags);

    // Draw
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);

      draw_inputs(input_flags);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

void get_inputs(int *input_flags) {
  *input_flags = 0;
  if (IsKeyPressed(KEY_W)) {
    *input_flags |= INPUT_UP;
  }
  if (IsKeyPressed(KEY_A)) {
    *input_flags |= INPUT_LEFT;
  }
  if (IsKeyPressed(KEY_S)) {
    *input_flags |= INPUT_DOWN;
  }
  if (IsKeyPressed(KEY_D)) {
    *input_flags |= INPUT_RIGHT;
  }
  if (IsKeyPressed(KEY_SPACE)) {
    *input_flags |= INPUT_SELECT;
  }
}

void draw_inputs(int input_flags) {
  float radius = 10;
  int x = 0;
  int y = 0;
  Color color;
  for (char i = 0; i < 5; i++) { // WARN: this is an 'unsafe' loop
    color = input_flags & (1 << i) ? RED : BLUE;
    DrawCircle(x + radius + 2 * radius * i, y + radius, radius, color);
  }
}
