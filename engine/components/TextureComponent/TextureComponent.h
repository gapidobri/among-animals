#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};
  bool tile = false, animated = false;
  int scale = 1, currentAnimationFrame = 0, animationFramesPerFrame = 10, currentFrame = 0, startFrame = 0, endFrame = 0;
  GameObjectState state = GameObjectState::Idle;
  char path[100]{};
  Bounds tileBounds = Bounds(0, 0, 0, 0);
  Size tileSize;

  void setup() override;

  void loop() override;

  void render(float x, float y);

public:

  TextureComponent();

  explicit TextureComponent(const char *filename);

  TextureComponent(const char *filename, int scale, bool animated, GameObjectState state);

  TextureComponent(const char *filename, int scale, bool animated, GameObjectState state, int startFrame, int endFrame);

  TextureComponent(const char *filename, int scale, Bounds tileBounds);

  TextureComponent(const char *filename, int scale, Position position, Size size);

  ComponentType type() override;

};

