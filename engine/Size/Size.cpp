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

Size Size::operator+(Size _size) const {
  return {width + _size.width, height + _size.height};
}

Size Size::operator/(int x) const {
  return {width / x, height / x};
}