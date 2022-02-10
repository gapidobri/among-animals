#pragma once

#include "../../Component/Component.h"
#include "../PhysicsComponent/PhysicsComponent.h"
#include "../TextureComponent/TextureComponent.h"

class NavigationComponent : public Component {

  PhysicsComponent *physicsComponent = nullptr;
  CollisionComponent *collisionComponent = nullptr;
  TextureComponent *textureComponent = nullptr;

  void setup() override;
  void loop() override;

public:
  ComponentType type() override;
};