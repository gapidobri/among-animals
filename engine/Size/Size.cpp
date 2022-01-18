#include "Size.h"

Size::Size() = default;

Size::Size(SDL_Rect rect) {
  width = rect.w;
  height = rect.h;
}

