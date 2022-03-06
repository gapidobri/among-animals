#pragma once

#include "../../Component/Component.h"
#include "../CollisionComponent/CollisionComponent.h"
#include "../PlayerComponent/PlayerComponent.h"

class AnimalComponent : public Component {

  float captureProgress = 0;
  void renderProgress();

  GameObject *player = nullptr;

  CollisionComponent *collisionComponent = nullptr;
  PlayerComponent *playerComponent = nullptr;

  void setup() override;
  void loop() override;


public:

  void setPlayer(GameObject *player);

};