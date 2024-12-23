#ifndef ORUGURU_H
#define ORUGURU_H

#include <raylib.h>
#include <stddef.h>
#include <stdint.h>

// Inputs
enum InputType {
  INPUT_UP = 1 << 0,
  INPUT_LEFT = 1 << 1,
  INPUT_DOWN = 1 << 2,
  INPUT_RIGHT = 1 << 3,
  INPUT_SELECT = 1 << 4,
};

struct InputMapping {
  KeyboardKey key;
  enum InputType input;
};

struct InputMap {
  size_t size;
  size_t capacity;
  struct InputMapping *map;
};

// Moves
#define moves_new(a, b, c, d)                                                  \
  ((d) << (3 * 8 * sizeof(uint8_t))) | ((c) << (2 * 8 * sizeof(uint8_t))) |    \
      ((b) << (1 * 8 * sizeof(uint8_t))) | ((a) << (0 * 8 * sizeof(uint8_t)))

#define moves_reset(m)                                                         \
  {                                                                            \
    m.curr = 0;                                                                \
    m.move = 0;                                                                \
  }

#define moves_print(m)                                                         \
  printf("%3d %3d %3d %3d\n",                                                  \
         ((uint8_t *)m)[0],                                                    \
         ((uint8_t *)m)[1],                                                    \
         ((uint8_t *)m)[2],                                                    \
         ((uint8_t *)m)[3]);

const uint32_t VALID_MOVES[] = {
    // Move Right
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_SELECT, INPUT_RIGHT),
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_RIGHT, INPUT_RIGHT),
    moves_new(INPUT_SELECT, INPUT_RIGHT, INPUT_RIGHT, INPUT_RIGHT),

    // Move Left
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_SELECT, INPUT_LEFT),
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_LEFT, INPUT_LEFT),
    moves_new(INPUT_SELECT, INPUT_LEFT, INPUT_LEFT, INPUT_LEFT),
};

// WARN(andrew): if we add more moves, this could break due to sizing.
// moves relies on uint8 being the size of `InputType`
struct Moves {
  uint8_t curr;
  union {
    uint32_t move;
    uint8_t moves[4];
  };
};

#endif // !ORUGURU_H