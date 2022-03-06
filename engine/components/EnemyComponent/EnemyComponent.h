#pragma once

#include "../../Component/Component.h"
#include "../PhysicsComponent/PhysicsComponent.h"

class EnemyComponent : public Component {

  std::vector<GameObjectState> availableStates = {};
  int nextState = 0;
  float movementSpeed = 0;

  GameObject *target;

  void setup() override;
  void loop() override;

  GameObjectState getRandomState();

public:

    void setTarget(GameObject *_target);

};