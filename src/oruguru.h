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
/* The type that states the size of InputType */
typedef uint8_t input_type;

/* all game recognized actions */
enum InputType {
  INPUT_UP = 1 << 0,
  INPUT_LEFT = 1 << 1,
  INPUT_DOWN = 1 << 2,
  INPUT_RIGHT = 1 << 3,
  INPUT_SELECT = 1 << 4,
};

/* to map key -> input */
struct InputMapping {
  KeyboardKey key;
  enum InputType input;
};

/* contains all mappings for game */
struct InputMap {
  size_t size;
  size_t capacity;
  struct InputMapping *map;
};

// Moves
/* creates a move little side first */
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
  dbg_print("%3d %3d %3d %3d\n", ((input_type *)m)[0], ((input_type *)m)[1],   \
            ((input_type *)m)[2], ((input_type *)m)[3]);

/* global for all game moves */
static const uint32_t VALID_MOVES[] = {
    // Move Right
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_SELECT, INPUT_RIGHT),
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_RIGHT, INPUT_RIGHT),
    moves_new(INPUT_SELECT, INPUT_RIGHT, INPUT_RIGHT, INPUT_RIGHT),

    // Move Left
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_SELECT, INPUT_LEFT),
    moves_new(INPUT_SELECT, INPUT_SELECT, INPUT_LEFT, INPUT_LEFT),
    moves_new(INPUT_SELECT, INPUT_LEFT, INPUT_LEFT, INPUT_LEFT),
};

/* move is a set of inputs */
struct Move {
  uint8_t curr;
  union {
    uint32_t fullInputs; // WARN(andrew): if we add more moves
                         // this could break due to sizing.
                         // moves relies on uint8 being the size of `InputType`
    input_type inputs[4];
  };
};

#endif // !ORUGURU_H
