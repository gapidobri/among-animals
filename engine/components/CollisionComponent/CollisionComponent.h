#pragma once

#include <vector>
#include "../../Component/Component.h"

class CollisionComponent : public Component {

  void setup() override;

  void loop() override;


public:

  ComponentType type() override;

  std::vector<GameObject *> getCollisions();
  std::vector<GameObject *> getCollisionsAfter(Position force);

  Position getCollisionDepth(GameObject *target);
  Position getCollisionDepthAfter(GameObject *target, Position force);

  bool isColliding();
  bool isCollidingAfter(Position force);

};