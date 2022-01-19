#include "Size.h"

Size::Size() = default;

Size::Size(int width, int height) {
  this->width = width;
  this->height = height;
}

Size::Size(SDL_Rect rect) {
  width = rect.w;
  height = rect.h;
}

