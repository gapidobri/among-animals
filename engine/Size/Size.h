#pragma once

#include <SDL2/SDL.h>

struct Size {
  float width{}, height{};

public:
  Size();

  Size(float, float);
  Size(int, int);

  explicit Size(SDL_FRect);

  Size operator+(Size _size) const;

  Size operator/(float x) const;
};
