#pragma once

#include "../../Component/Component.h"
#include "../CollisionComponent/CollisionComponent.h"
#include <chrono>

class PhysicsComponent : public Component {

  float speed = 0, direction = 0, bounciness = 0;
  bool dynamic = true;

  CollisionComponent *collisionComponent{};

  void setup() override;

  void loop() override;

  static float calcDirection(float, float);

public:
  PhysicsComponent();

  explicit PhysicsComponent(float bounciness);

  explicit PhysicsComponent(bool dynamic);

  PhysicsComponent(bool dynamic, float bounciness);

  void applyForce(float direction, float speed);

  void setSpeedX(float speedX);

  void setSpeedY(float speedY);

  ComponentType type() override;

};