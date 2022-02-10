#include "Size.h"

Size::Size() = default;

Size::Size(float width, float height) {
  this->width = width;
  this->height = height;
}

Size::Size(SDL_FRect rect) {
  width = rect.w;
  height = rect.h;
}

Size Size::operator+(Size _size) const {
  return {width + _size.width, height + _size.height};
}

Size Size::operator/(float x) const {
  return {width / x, height / x};
}

Size::Size(int width, int height) {
  this->width = (float) width;
  this->height = (float) height;
}
