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

Position::Position(Size size) {
  this->x = size.width;
  this->y = size.height;
}

Position Position::operator+(Position _pos) const {
  return Position{x + _pos.x, y + _pos.y};
}

void Position::operator+=(Position _pos) {
  x += _pos.x;
  y += _pos.y;
}

Position Position::operator-(Position _pos) const {
  return Position{x - _pos.x, y - _pos.y};
}

