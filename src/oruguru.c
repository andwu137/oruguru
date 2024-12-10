#include <raylib.h>
#include <raymath.h>

typedef struct Effect {
  Vector2 vector;
  int innerRadius;
  int outerRadius;
  char exist;
} Effect;

void spawnEffect(Effect *e, Vector2 v) {
  e->vector = v;
  e->innerRadius = 5;
  e->outerRadius = 10;
  e->exist = 1;
}

void drawEffect(Effect *e) {
    if (e->exist) {
      DrawRing(e->vector, e->innerRadius, e->outerRadius, 0, 360, 0, YELLOW);
    }
    e->innerRadius += 5;
    e->outerRadius += 4;

    if (e->innerRadius >= e->outerRadius) {
      e->exist = 0;
    }
}

int
main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "oruguru");

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
  Vector2 v = {100, 100};
  Effect effect;
  spawnEffect(&effect, v);
    // Update

    // Draw
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);
      ClearBackground(DARKGRAY);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);
      drawEffect(&effect);
    }
    EndDrawing();
    if (effect.exist == 0) {
      effect.exist = 1;
      spawnEffect(&effect, v);
    }
  }

  CloseWindow();
  return 0;
}
