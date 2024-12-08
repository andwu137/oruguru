#ifndef ORUGURU_H
#define ORUGURU_H

#include <raylib.h>
#include <stddef.h>

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

#endif // !ORUGURU_H
