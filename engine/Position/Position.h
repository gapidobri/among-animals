#pragma once

#include <SDL2/SDL.h>

struct Position {
  int x{}, y{};

public:
  Position();
  Position(int, int);
  explicit Position(SDL_Rect);

  Position operator+(Position) const;
  Position operator-(Position) const;
};