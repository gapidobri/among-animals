#pragma once

#include "../../Component/Component.h"

class ProjectileComponent : public Component {

  Position position;


  void setup() override;

  void loop() override;

public:

  ComponentType type() override;

};

