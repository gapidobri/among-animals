#pragma once

#include "../../Component/Component.h"

class FixedPositionComponent : public Component {

  Position position;

  void setup() override;

  void loop() override;

public:
  FixedPositionComponent(int, int);

  ComponentType type() override;

};
