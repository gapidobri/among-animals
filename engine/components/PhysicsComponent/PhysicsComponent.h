#pragma once

#include "../../Component/Component.h"
#include "../CollisionComponent/CollisionComponent.h"
#include <chrono>

class PhysicsComponent : public Component {

  double speed = 0, direction = 0, bounciness = 0;
  bool dynamic = true;

  CollisionComponent *collisionComponent{};

  void setup() override;

  void loop() override;

  static double calcDirection(double, double);

public:
  PhysicsComponent();

  explicit PhysicsComponent(double bounciness);

  explicit PhysicsComponent(bool dynamic);

  PhysicsComponent(bool dynamic, double bounciness);

  void applyForce(double direction, double speed);

  void setSpeedX(double speedX);

  void setSpeedY(double speedY);

  ComponentType type() override;

};