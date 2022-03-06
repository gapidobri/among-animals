#pragma once

#include "../Size/Size.h"

class Position {

public:
  float x, y;

  Position();

  Position(Size size);

  Position(float x, float y);

  Position operator+(Position _position) const;

  Position operator-(Position _position) const;

  void operator+=(Position _position);

  void operator-=(Position _position);

};