#pragma once

#include "../../Component/Component.h"
#include "../CollisionComponent/CollisionComponent.h"
#include <chrono>
#include <fstream>

class PhysicsComponent : public Component {

  float speed = 0, direction = 0, bounciness = 0;
  bool dynamic = true;

  std::ofstream ofstream;
  std::ifstream ifstream;

  CollisionComponent *collisionComponent{};

  void setup() override;
  void loop() override;
  void end() override;

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

struct State {
  float speed, direction;
  bool flip;
};