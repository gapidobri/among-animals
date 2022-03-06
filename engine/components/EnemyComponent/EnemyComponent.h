#pragma once

#include "../../Component/Component.h"
#include "../PhysicsComponent/PhysicsComponent.h"
#include "../PlayerComponent/PlayerComponent.h"

class EnemyComponent : public Component {

  std::vector<GameObjectState> availableStates = {};
  int nextState = 0;
  float movementSpeed = 0;

  GameObject *target;

  void setup() override;
  void loop() override;

  GameObjectState getRandomState();

  CollisionComponent *collisionComponent = nullptr;
  PlayerComponent *targetPlayerComponent = nullptr;

public:

    void setTarget(GameObject *_target);

};