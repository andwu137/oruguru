#ifndef ORUGURU_H
#define ORUGURU_H

#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdint.h>

// Helpers
#ifdef DEBUG
#define dbg_print printf
#define dbg_puts puts
#define dbg_assert assert
#else
#define dbg_print(...)
#define dbg_puts(...)
#define dbg_assert(_)
#endif

// Inputs
typedef uint8_t input_type;

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
  ((d) << (3 * 8 * sizeof(input_type))) |                                      \
      ((c) << (2 * 8 * sizeof(input_type))) |                                  \
      ((b) << (1 * 8 * sizeof(input_type))) |                                  \
      ((a) << (0 * 8 * sizeof(input_type)))

#define moves_reset(m)                                                         \
  {                                                                            \
    m.curr = 0;                                                                \
    m.move = 0;                                                                \
  }

#define moves_print(m)                                                         \
  printf("%3d %3d %3d %3d\n", ((input_type *)m)[0], ((input_type *)m)[1],      \
         ((input_type *)m)[2], ((input_type *)m)[3]);

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

struct Moves {
  uint8_t curr;
  union {
    uint32_t move; // WARN(andrew): if we add more moves
                   // this could break due to sizing.
                   // moves relies on uint8 being the size of `InputType`
    input_type moves[4];
  };
};

#endif // !ORUGURU_H
