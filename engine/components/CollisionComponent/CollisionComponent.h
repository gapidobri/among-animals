#pragma once

#include <vector>
#include "../../Component/Component.h"

class CollisionComponent : public Component {

  std::vector<GameObject *> collisions;
  std::vector<GameObject *> collisionsX;
  std::vector<GameObject *> collisionsY;

  void setup() override;

  void loop() override;


public:

  ComponentType type() override;

  std::vector<GameObject *> getCollisions();

  std::vector<GameObject *> getCollisions(Position offset);

  Position getCollisionDepth(GameObject *target);

  std::vector<GameObject *> getCollisionsX();
  std::vector<GameObject *> getCollisionsY();

  bool isColliding();

};