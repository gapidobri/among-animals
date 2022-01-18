#include "Position.h"

Position::Position() = default;

Position::Position(int x, int y) {
  this->x = x;
  this->y = y;
}

Position::Position(SDL_Rect rect) {
  x = rect.x;
  y = rect.y;
}

