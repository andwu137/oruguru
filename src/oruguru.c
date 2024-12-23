#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

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

void draw_button(Vector2 topLeft, int width, int height, int fontSize,
                 const char *text, bool isSelected) {
  int margin = 10;
  Color topColor, bottomColor, textColor;

  if (isSelected) {
    topColor = RED;
    bottomColor = (Color){.r = 205, .g = 25, .b = 35, .a = 255};
    textColor = (Color){.r = 240, .g = 190, .b = 20, .a = 255};
  } else {
    topColor = DARKGRAY;
    bottomColor = BLACK;
    textColor = WHITE;
  }

  DrawRectangleGradientV(topLeft.x, topLeft.y, width, height, topColor,
                         bottomColor);
  DrawText(text, topLeft.x + margin, topLeft.y + fontSize / 2, fontSize,
           textColor);
}

void draw_pause(int buttonWidth, int buttonHeight, int fontSize,
                int selected /* temp */) {
  int lineLength = GetScreenHeight() * 0.05;
  int thickness = GetScreenWidth() * 0.01;
  Vector2 lineStart = {.x = 20, .y = 20};
  Vector2 lineEnd = {.x = lineStart.x, .y = lineStart.y + lineLength};
  Vector2 buttonV = {.x = GetScreenWidth() / 2 - buttonWidth / 2,
                     .y = GetScreenHeight() / 2 - buttonHeight * 1.25};
  Color color = BLACK;
  color.a = 100;

  // Overlay
  DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), color);

  // Pause Symbol
  DrawLineEx(lineStart, lineEnd, thickness, WHITE);
  lineStart.x = lineStart.x + thickness * 1.5;
  lineEnd.x = lineEnd.x + thickness * 1.5;
  DrawLineEx(lineStart, lineEnd, thickness, WHITE);

  // Buttons
  draw_button(buttonV, buttonWidth, buttonHeight, fontSize, "RESUME", true);
  buttonV.y = buttonV.y + buttonHeight * 1.25;
  draw_button(buttonV, buttonWidth, buttonHeight, fontSize, "QUIT", false);
}

void draw_mania_meter(int percentage) {
  int margin = 5;
  float p = (float)percentage / 100;
  int fontSize = 20;
  int width = GetScreenWidth() * 0.33;
  int height = GetScreenHeight() * 0.1;
  int progressWidth = (width - 2 * margin) * p;
  char str[4];
  Vector2 topLeft = {.x = GetScreenWidth() / 2 - width / 2, .y = 10};
  itoa(percentage, str, 10);
  str[2] = '%';

  DrawRectangle(topLeft.x, topLeft.y, width, height, BLACK);
  DrawRectangle(topLeft.x + margin, topLeft.y + margin, width - 2 * margin,
                height - 2 * margin, WHITE);
  DrawRectangle(topLeft.x + margin, topLeft.y + margin, progressWidth,
                height - 2 * margin, RED);

  if (percentage >= 10) {
    DrawText(str, topLeft.x + progressWidth / 2 - fontSize / 2,
             topLeft.y + 2 * margin, fontSize, YELLOW);
  }
}

int main(int argc, char *argv[]) {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "oruguru");

  SetTargetFPS(60);

  int percentage = 20;

  while (!WindowShouldClose()) {
    // Update
    Vector2 v = {.x = 100, .y = 100};

    // Draw
    BeginDrawing();
    {
      ClearBackground(DARKGRAY);
      DrawText("oruguru", 190, 200, 20, LIGHTGRAY);
      draw_health(v, 3, 3);
      draw_mania_meter(percentage);
      draw_pause(200, 50, 20, 1);
    }
    EndDrawing();

    percentage++;
    percentage = percentage % 101;
  }

  CloseWindow();
  return 0;
}
