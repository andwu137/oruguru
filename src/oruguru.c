#include "oruguru.h"
#include "oruguru_inputs.c"
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

/* FUNCTIONS */
int
main(int argc, char *argv[]) {
  const uint16_t screenWidth = 800;
  const uint16_t screenHeight = 450;

  long long inputFlags;
  struct InputMap inputMap;
  input_map_default(1 << 4, &inputMap);

  struct Moves moves = {.curr = 0, .move = 0};
  uint8_t tempMove;
  int8_t resultMove;

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

#ifdef DEBUG
      printf("Move #%d\n", moves.curr);
#endif
      input_flags_debug_draw(inputFlags);
      if ((tempMove = get_move(inputFlags)) != 0) {
        moves.moves[moves.curr++] = tempMove;
      } else {
        // TODO(andrew): moves_reset(moves);
      }

      if (moves.curr >= 4) {
        if ((resultMove = valid_move(&moves)) != -1) {
#ifdef DEBUG
          printf("MOVE(%d): ", resultMove);
          moves_print(moves.moves);
#endif
        }
        moves_reset(moves);
      }
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
