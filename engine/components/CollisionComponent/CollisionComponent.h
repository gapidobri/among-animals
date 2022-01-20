#pragma once

#include <vector>
#include "../../Component/Component.h"

class CollisionComponent : public Component {

  std::vector<GameObject *> collisions;

  void setup() override;

  void loop() override;

public:

  ComponentType type() override;

  std::vector<GameObject *> getCollisions();

  std::vector<GameObject *> getCollisions(Position offset);

  bool isColliding();

  bool isColliding(Position offset);

};