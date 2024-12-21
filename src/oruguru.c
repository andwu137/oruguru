#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

union EffectData {
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
};

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

  union EffectData start;
  union EffectData end;
};

void
spawn_effect(struct Effect *e, int type, Vector2 pos, Color color) {
  e->pos = pos;
  e->completion = 0;
  e->speed = 1;
  e->color = color;
  e->type = type;

  switch (type) {
  case EFFECT_RING: {
    e->start.ring.innerRadius = 5;
    e->start.ring.outerRadius = 10;
    e->end.ring.innerRadius = 30;
    e->end.ring.outerRadius = 30;
  } break;
  case EFFECT_SCREEN_BORDER: {
    e->start.screenBorder.thickness = 10;
    e->end.screenBorder.thickness = 3;
  } break;
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
  } break;
  case EFFECT_SCREEN_BORDER: {
    float thickDiff =
        e->end.screenBorder.thickness - e->start.screenBorder.thickness;
    float currThick =
        e->start.screenBorder.thickness + thickDiff * e->completion;
    Rectangle rec = {
        .height = GetScreenHeight(), .width = GetScreenWidth(), .x = 0, .y = 0};
    DrawRectangleLinesEx(rec, currThick, e->color);
  } break;
  case EFFECT_TRANSLATE: {
  } break;
  }

  e->completion += 0.1 * e->speed;
}

void
draw_judgeline(Vector2 center) {
  int height = 60;
  int width = 5;

  Rectangle rec1 = {center.x - width / 2, center.y - height / 2, width, height};
  DrawRectangleRec(rec1, BLACK);
}

void
draw_circle_input(Vector2 center, int radius, int i /*, enum InputType i*/) {
  Vector2 angles[12] = {
      // UP ARROW
      {.x = 0, .y = 1},
      {.x = -sqrt(3) / 2, .y = -1 / 2},
      {.x = sqrt(3) / 2, .y = -1 / 2},
      // DOWN ARROW
      {.x = 0, .y = -1},
      {.x = -sqrt(3) / 2, .y = 1 / 2},
      {.x = sqrt(3) / 2, .y = 1 / 2},
      // LEFT ARROW
      {.x = -1, .y = 0},
      {.x = 1 / 2, .y = -sqrt(3) / 2},
      {.x = 1 / 2, .y = sqrt(3) / 2},
      // RIGHT ARROW
      {.x = 1, .y = 0},
      {.x = 1 / 2, .y = -sqrt(3) / 2},
      {.x = 1 / 2, .y = sqrt(3) / 2},
  };
  Color palette[6] = {
      GetColor(0x39B54AFF), // GREEN
      GetColor(0xF15A29FF), // ORANGE
      GetColor(0x00A3E0FF), // BLUE
      GetColor(0xD5006DFF), // MAGENTA
      GetColor(0xFBB03BFF), // YELLOW
  };
  // Up = 0, Down = 1, Left = 2, Right = 3
  Vector2 *angle = &(angles[3 * (i % 4)]);
  Vector2 points[3];

  points[0] = (Vector2){.x = center.x + radius * angle->x,
                        .y = center.y + radius * angle->y};
  points[1] = (Vector2){.x = center.x + radius * (angle + 1)->x,
                        .y = center.y + radius * (angle + 1)->y};
  points[2] = (Vector2){.x = center.x + radius * (angle + 2)->x,
                        .y = center.y + radius * (angle + 2)->y};
  if (i < 2) {
    // Vertical
    points[0].y = points[0].y - 3 * angle->y;
    points[1].y = points[1].y - 9 * angle->y;
    points[2].y = points[2].y - 9 * angle->y;

  } else if (i < 4) {
    // Horizontal
    points[0].x = points[0].x - 3 * angle->x;
    points[1].x = points[1].x - 9 * angle->x;
    points[2].x = points[2].x - 9 * angle->x;
  } else {
    // Space input
    points[0].y = center.y;
  }

  DrawCircleV(center, radius / 1.20, palette[i]);
  DrawLineEx(points[0], points[1], 3, WHITE);
  DrawLineEx(points[0], points[2], 3, WHITE);
  DrawLineEx(points[1], points[2], 3, WHITE);
  DrawRing(center, radius - 2.5, radius, 0, 360, 0, BLACK);
}

// TODO(Daria): This function needs to accept player's input
// (e.g. UP, DOWN, LEFT, RIGHT, <Space>) maybe as an array.
void
draw_visual_helper() {
  int length = 300;
  int thickness = 5;
  int height = 40; // for end bars

  int square = length / 8; // for spacing
  int radius = height / 2;

  Vector2 start, end;
  int startPoint[] = {GetScreenWidth() / 2 - length / 2,
                      GetScreenHeight() / 1.20};
  int endPoint[] = {GetScreenWidth() / 2 + length / 2,
                    GetScreenHeight() / 1.20};
  Vector2 center = {startPoint[0] + square, startPoint[1]};

  // MAIN LINE
  start.x = startPoint[0];
  start.y = startPoint[1];
  end.x = endPoint[0];
  end.y = endPoint[1];
  DrawLineEx(start, end, thickness, BLACK);

  // LEFT END BAR
  start.y = startPoint[1] - height / 2;
  end.y = startPoint[1] + height / 2;
  end.x = startPoint[0];
  DrawLineEx(start, end, thickness, BLACK);

  // RIGHT END BAR
  start.x = endPoint[0];
  end.x = start.x;
  DrawLineEx(start, end, thickness, BLACK);

  for (int i = 0; i < 4; i++) {
    // NOTE(Daria): change this after merging with input detection

    // Empty Circle
    // DrawCircleV(center, radius, BLACK);
    // DrawCircleV(center, radius / 1.20, WHITE);

    draw_circle_input(center, radius, i);

    center.x += square * 2;
  }
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
      draw_visual_helper();
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
