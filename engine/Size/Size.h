#pragma once

#include <SDL2/SDL.h>

struct Size {
  int width{}, height{};

public:
  Size();
  Size(int, int);
  explicit Size(SDL_Rect);
};
