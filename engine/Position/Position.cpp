#include "Position.h"

Position::Position() {
  x = 0;
  y = 0;
}

Position::Position(float x, float y) {
  this->x = x;
  this->y = y;
}

Position::Position(Size size) {
  this->x = size.width;
  this->y = size.height;
}

void Position::operator+=(Position _position) {
  this->x += _position.x;
  this->y += _position.y;
}

Position Position::operator+(Position _position) const {
  return {this->x + _position.x, this->y + _position.y};
}

Position Position::operator-(Position _position) const {
  return {this->x - _position.x, this->y - _position.y};
}
