#ifndef ORUGURU_INPUTS_C
#define ORUGURU_INPUTS_C

#include "oruguru.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPES */
void input_flags_debug_draw(input_type inputFlags);
void input_map_read(struct InputMap *inputMap, input_type *inputFlags);
void input_map_init(size_t initCap, struct InputMap *inputMap);
void input_map_default(size_t initCap, struct InputMap *inputMap);
void input_map_push(struct InputMap *inputMap, struct InputMapping im);

void valid_moves_default(input_type *validMoves);
uint8_t get_move(input_type inputFlags);
int8_t valid_move(struct Move *moves);

/* FUNCTIONS */
// INPUTS
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
  input_map_init(initCap, inputMap);
  {
    input_map_push(inputMap,
                   ((struct InputMapping){.key = KEY_W, .input = INPUT_UP}));
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_A, .input = INPUT_LEFT});
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_S, .input = INPUT_DOWN});
    input_map_push(inputMap,
                   (struct InputMapping){.key = KEY_D, .input = INPUT_RIGHT});
    input_map_push(inputMap, (struct InputMapping){.key = KEY_SPACE,
                                                   .input = INPUT_SELECT});
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
input_map_read(struct InputMap *inputMap, input_type *inputFlags) {
  *inputFlags = 0;
  for (size_t i = 0; i < inputMap->size; i++) {
    if (IsKeyPressed(inputMap->map[i].key)) {
      *inputFlags |= inputMap->map[i].input;
    }
  }
}

void
input_flags_debug_draw(input_type inputFlags) {
  float radius = 10;
  uint16_t x = 0;
  uint16_t y = 0;
  Color color;
  for (uint8_t i = 0; i < sizeof(inputFlags) * 8; i++) {
    color = inputFlags & (1 << i) ? RED : BLUE;
    DrawCircle(x + radius + 2 * radius * i, y + radius, radius, color);
  }
}

// MOVES
input_type
get_move(input_type inputFlags) {
  for (uint8_t i = 0; i < sizeof(inputFlags) * 8; i++) {
    if (inputFlags == (((input_type)1) << i)) {
      return inputFlags;
    }
  }

  return false;
}

int8_t
valid_move(struct Move *move) {
  for (uint8_t i = 0; i < sizeof(VALID_MOVES) / sizeof(*VALID_MOVES); i++) {
    if (*((uint32_t *)VALID_MOVES[i]) == move->fullInputs) {
      return i;
    }
  }

  return -1;
}

#endif // !ORUGURU_INPUTS_C
