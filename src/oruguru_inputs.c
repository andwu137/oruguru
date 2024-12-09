#ifndef ORUGURU_INPUTS_C
#define ORUGURU_INPUTS_C

#include "oruguru.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPES */
void
draw_inputs(int input_flags);
void
input_map_read(struct InputMap *inputMap, long long *inputFlags);
void
input_map_init(size_t initCap, struct InputMap *inputMap);
void
input_map_default(size_t initCap, struct InputMap *inputMap);
void
input_map_push(struct InputMap *inputMap, struct InputMapping im);

/* FUNCTIONS */
void
input_map_init(size_t initCap, struct InputMap *inputMap) {
  inputMap->size = 0, inputMap->capacity = initCap,
  inputMap->map = calloc(initCap, sizeof(*inputMap->map));
  if (inputMap->map == NULL) {
    perror("inputMap: failed to alloc");
    abort();
  }
}

void
input_map_default(size_t initCap, struct InputMap *inputMap) {
  input_map_init(1 << 4, inputMap);
  {
    input_map_push(inputMap,
                   ((struct InputMapping){.key = KEY_W, .input = INPUT_UP}));
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_A, .input = INPUT_LEFT});
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_S, .input = INPUT_DOWN});
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_D, .input = INPUT_RIGHT});
    input_map_push(
        inputMap,
        (struct InputMapping){.key = KEY_SPACE, .input = INPUT_SELECT});
  }
}

void
input_map_push(struct InputMap *inputMap, struct InputMapping im) {
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

void
input_map_read(struct InputMap *inputMap, long long *inputFlags) {
  *inputFlags = 0;
  for (size_t i = 0; i < inputMap->size; i++) {
    if (IsKeyPressed(inputMap->map[i].key)) {
      *inputFlags |= inputMap->map[i].input;
    }
  }
}

void
input_flags_debug_draw(int inputFlags) {
  float radius = 10;
  int x = 0;
  int y = 0;
  Color color;
  for (char i = 0; i < sizeof(int) * 8; i++) {
    color = inputFlags & (1 << i) ? RED : BLUE;
    DrawCircle(x + radius + 2 * radius * i, y + radius, radius, color);
  }
}

#endif // !ORUGURU_INPUTS_C
