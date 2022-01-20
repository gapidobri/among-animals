#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};
  bool tile = false;
  int scale = 1;
  char path[100]{};
  Bounds tileBounds = Bounds(0, 0, 0, 0);
  Size tileSize;

  void setup() override;

  void loop() override;

  void render(int x, int y);

public:

  explicit TextureComponent(const char *filename);

  TextureComponent(const char *filename, bool tile);

  TextureComponent(const char *filename, int scale, bool tile);

  TextureComponent(const char *filename, int scale, Bounds tileBounds);

  TextureComponent(const char *filename, int scale, Position position, Size size);

  ComponentType type() override;

};

