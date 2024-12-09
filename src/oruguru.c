#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

struct Effect {
  Vector2 pos;
  double completion; // range [0, 1]
  float speed;       // 1 = normal, 2 = twice as fast
  Color color;

  enum {
    EFFECT_RING,
    EFFECT_SCREEN_BORDER,
    EFFECT_TRANSLATE
  } type;

  union {
    struct {
      int innerRadius;
      int outerRadius;
    } ring;

    struct {
      float thickness;
    } screenBorder;

    struct {
      Vector2 position;
    } translate;
  } start;

  union {
    struct {
      int innerRadius;
      int outerRadius;
    } ring;

    struct {
      int thickness;
    } screenBorder;

    struct {
      Vector2 position;
    } translate;
  } end;
};

void
spawn_effect(struct Effect *e, int type, Vector2 pos, Color color) {
  e->pos = pos;
  e->completion = 0;
  e->speed = 1;
  e->color = color;
  e->type = type;

  switch (type) {
  case EFFECT_RING:
    e->start.ring.innerRadius = 5;
    e->start.ring.outerRadius = 10;
    e->end.ring.innerRadius = 30;
    e->end.ring.outerRadius = 30;
    break;
  case EFFECT_SCREEN_BORDER:
    e->start.screenBorder.thickness = 10;
    e->end.screenBorder.thickness = 3;
    break;
  }
}

void
draw_effect(struct Effect *e) {
  if (e->completion >= 1) {
    e->completion = 1;
    return;
  }

  switch (e->type) {
  case EFFECT_RING: {
    float innerDiff = e->end.ring.innerRadius - e->start.ring.innerRadius;
    float outerDiff = e->end.ring.outerRadius - e->start.ring.outerRadius;

    float currInner = e->start.ring.innerRadius + innerDiff * e->completion;
    float currOuter = e->start.ring.outerRadius + outerDiff * e->completion;

    DrawRing(e->pos, currInner, currOuter, 0, 360.0f, 0, e->color);
    break;
  }
  case EFFECT_SCREEN_BORDER: {
    float thickDiff =
        e->end.screenBorder.thickness - e->start.screenBorder.thickness;
    float currThick =
        e->start.screenBorder.thickness + thickDiff * e->completion;
    Rectangle rec = {
        .height = GetScreenHeight(), .width = GetScreenWidth(), .x = 0, .y = 0};
    DrawRectangleLinesEx(rec, currThick, e->color);
    break;
  }
  case EFFECT_TRANSLATE: {
    break;
  }
  }

  e->completion += 0.1 * e->speed;
}

int
main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "oruguru");

  SetTargetFPS(60);

  Vector2 v = {.x = 100, .y = 100};
  struct Effect e1, e2;
  spawn_effect(&e1, EFFECT_RING, v, YELLOW);
  spawn_effect(&e2, EFFECT_SCREEN_BORDER, v, RED);

  while (!WindowShouldClose()) {
    // Update

    // Draw
    BeginDrawing();
    {
      ClearBackground(DARKGRAY);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);
      draw_effect(&e1);
      draw_effect(&e2);
    }
    EndDrawing();

    // Temporary
    if (e1.completion >= 1) {
      spawn_effect(&e1, EFFECT_RING, v, YELLOW);
    }
    if (e2.completion >= 1) {
      spawn_effect(&e2, EFFECT_SCREEN_BORDER, v, RED);
    }
  }

  CloseWindow();
  return 0;
}
