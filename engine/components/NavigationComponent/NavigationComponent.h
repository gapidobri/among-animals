#pragma once

#include "../../Component/Component.h"
#include "../PhysicsComponent/PhysicsComponent.h"

class NavigationComponent : public Component {

  PhysicsComponent *physicsComponent{};
  CollisionComponent *collisionComponent{};

  void setup() override;
  void loop() override;

public:
  ComponentType type() override;
};