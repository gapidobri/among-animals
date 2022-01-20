#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};
  bool tile = false;
  char path[100]{};

  void setup() override;

  void loop() override;

  void render(int x, int y);

public:

  explicit TextureComponent(const char *filename);

  TextureComponent(const char *filename, bool tile);

  ComponentType type() override;

};

