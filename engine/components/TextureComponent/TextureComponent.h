#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};

  void setup() override;
  void loop() override;

public:

  ComponentType type() override;

};

