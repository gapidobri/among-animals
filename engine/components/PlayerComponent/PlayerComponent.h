#pragma once

#include "../../Component/Component.h"
#include "../TextureComponent/TextureComponent.h"

class PlayerComponent : public Component {

  int health = 10;
  int animalsCollected = 0;
  int godMode = 0;
  int blinkTime = 10;
  int animalCount = 0;

  void setup() override;
  void loop() override;

  ComponentType type() override;

public:
  PlayerComponent();
  explicit PlayerComponent(int health, int animalCount);

  void damage();
  void animalCollected();

  void renderAnimalsCollected();
  void renderHealth();
};