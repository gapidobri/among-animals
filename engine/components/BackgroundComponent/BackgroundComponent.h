#pragma once

#include "../../Component/Component.h"

class BackgroundComponent : public Component {

  SDL_Texture *texture;

  char path[100]{};
  double z = 1;

  void setup() override;
  void loop() override;

public:
  explicit BackgroundComponent(const char *filename);

  BackgroundComponent(const char *filename, double z);

  ComponentType type() override;

};