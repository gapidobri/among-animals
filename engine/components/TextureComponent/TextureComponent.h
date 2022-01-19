#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};

  void setup() override;

  void loop() override;

  char path[99]{};

public:
  explicit TextureComponent(const char *);

  ComponentType type() override;

};

