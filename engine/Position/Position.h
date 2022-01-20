#pragma once

#include <SDL2/SDL.h>
#include "../Size/Size.h"

struct Position {
  Position(Size size);

  int x{}, y{};

public:
  Position();
  Position(int, int);
  explicit Position(SDL_Rect);

  Position operator+(Position) const;
  Position operator-(Position) const;
};