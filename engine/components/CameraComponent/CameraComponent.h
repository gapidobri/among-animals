#pragma once

#include "../../Component/Component.h"

class CameraComponent : public Component {

  void setup() override;
  void loop() override;

public:

  ComponentType type() override;

};