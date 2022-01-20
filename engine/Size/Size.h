#pragma once

#include <SDL2/SDL.h>

struct Size {
  int width{}, height{};

public:
  Size();

  Size(int, int);

  explicit Size(SDL_Rect);

  Size operator+(Size _size) const;

  Size operator/(int x) const;
};
