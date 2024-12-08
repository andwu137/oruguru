#ifndef ORUGURU_INPUTS_C
#define ORUGURU_INPUTS_C

#include "oruguru.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPES */
void draw_inputs(int input_flags);
void input_map_read(struct InputMap *inputMap, int *inputFlags);
void input_map_default(size_t initCap, struct InputMap *inputMap);

/* FUNCTIONS */
void input_map_default(size_t initCap, struct InputMap *inputMap) {
  inputMap->size = 0, inputMap->capacity = initCap,
  inputMap->map = calloc(initCap, sizeof(*inputMap->map));
  if (inputMap->map == NULL) {
    perror("inputMap: failed to alloc");
    abort();
  }
}

void input_map_push(struct InputMap *inputMap, struct InputMapping im) {
  if (inputMap->size == inputMap->capacity) {
    inputMap->capacity <<= 1;
    inputMap->map =
        realloc(inputMap->map, inputMap->capacity * sizeof(*inputMap->map));
    if (inputMap->map == NULL) {
      perror("inputMap: failed to alloc");
      abort();
    }
  }

  inputMap->map[inputMap->size++] = im;
}

void input_map_read(struct InputMap *inputMap, int *inputFlags) {
  *inputFlags = 0;
  for (size_t i = 0; i < inputMap->size; i++) {
    if (IsKeyPressed(inputMap->map[i].key)) {
      *inputFlags |= inputMap->map[i].input;
    }
  }
}

void draw_inputs(int inputFlags) {
  float radius = 10;
  int x = 0;
  int y = 0;
  Color color;
  for (char i = 0; i < 5; i++) { // WARN: this is an 'unsafe' loop
    color = inputFlags & (1 << i) ? RED : BLUE;
    DrawCircle(x + radius + 2 * radius * i, y + radius, radius, color);
  }
}

#endif // !ORUGURU_INPUTS_C
