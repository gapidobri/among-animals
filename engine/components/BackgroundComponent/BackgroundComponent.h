#pragma once

#include "../../Component/Component.h"

class BackgroundComponent : public Component {

  SDL_Texture *texture{};

  char path[100]{};
  float z = 1;

  void setup() override;
  void loop() override;

public:
  explicit BackgroundComponent(const char *filename);

  BackgroundComponent(const char *filename, float z);

  ComponentType type() override;

};