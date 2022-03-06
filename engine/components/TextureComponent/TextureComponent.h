#pragma once

#include "../../Component/Component.h"

class TextureComponent : public Component {

  SDL_Renderer *renderer{};
  SDL_Texture *texture{};
  bool tile = false, animated = false;
  float scale = 1;
  int currentAnimationFrame = 0, animationFramesPerFrame = 10, currentFrame = 0, startFrame = 0, endFrame = 0, frameCount = 1;
  GameObjectState state = GameObjectState::Idle;
  char path[100] {};
  Bounds tileBounds = Bounds(0, 0, 0, 0);
  Size tileSize;
  int cropLeft = 0, cropTop = 0, cropRight = 0, cropBottom = 0;

  void setup() override;

  void loop() override;

  void render(float x, float y);

public:

  TextureComponent();

  explicit TextureComponent(const char *filename);

  TextureComponent(const char *filename, float scale, bool animated, GameObjectState state);

  TextureComponent(const char *filename, float scale, bool animated, GameObjectState state, int startFrame, int endFrame);

  TextureComponent(const char *filename, float scale, Bounds tileBounds);

  TextureComponent(const char *filename, float scale, Position position, Size size);

  TextureComponent* applyCrop(int left, int top, int right, int bottom);

  TextureComponent* setScale(float scale);

  TextureComponent* setFrameCount(int frames);

  ComponentType type() override;

};

