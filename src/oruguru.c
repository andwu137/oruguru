#include "oruguru.h"
#include "oruguru_inputs.c"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

/* PROTOTYPES */

/* FUNCTIONS */
int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;
  int inputFlags;
  struct InputMap inputMap;
  input_map_default(1 << 4, &inputMap);

  InitWindow(screenWidth, screenHeight, "oruguru");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    // Update
    input_map_read(&inputMap, &inputFlags);

    // Draw
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);

      input_flags_debug_draw(inputFlags);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
