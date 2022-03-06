#include "TextureComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TextureComponent::TextureComponent() = default;

TextureComponent::TextureComponent(const char *filename) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
}

TextureComponent::TextureComponent(const char *filename, float scale, bool animated, GameObjectState state) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->animated = animated;
  this->state = state;
}

TextureComponent::TextureComponent(const char *filename, float scale, bool animated, GameObjectState state,
                                   int startFrame, int endFrame) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->animated = animated;
  this->state = state;
  this->startFrame = startFrame;
  this->endFrame = endFrame;
}

TextureComponent::TextureComponent(const char *filename, float scale, Bounds tileBounds) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->tile = true;
  this->tileBounds = tileBounds;
}

TextureComponent::TextureComponent(const char *filename, float scale, Position position, Size size) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->tile = true;
  this->tileBounds = {position.x, position.x + size.width, position.y, position.y + size.height};
}

void TextureComponent::setup() {
  Component::setup();

  renderer = getRenderer();
  texture = IMG_LoadTexture(renderer, path);

  if (!texture) {
    std::cout << "Texture load failed\n" << IMG_GetError() << '\n';
  }

  int texWidth, texHeight;
  SDL_QueryTexture(texture, nullptr, nullptr, &texWidth, &texHeight);
  if (animated) {
    texWidth /= frameCount;
  }

  Size size = gameObject->getSize();

  if (!tile) {
    gameObject->setSize({size.width == 0 ? (float) texWidth * scale - (float) cropLeft - (float) cropRight : size.width,
                         size.height == 0 ? (float) texHeight * scale - (float) cropTop - (float) cropBottom : size.height});
  }

  if (animated && startFrame == 0 && endFrame == 0) {
    endFrame = (int) (texWidth / texHeight);
  }

  tileSize = {texWidth, texHeight};
}

void TextureComponent::loop() {

  Component::loop();

  if (gameObject->getState() != state) {
    currentFrame = 0;
    currentAnimationFrame = startFrame;
    return;
  }

  auto renderPosition = gameObject->getRenderPosition();
  auto windowSize = gameObject->getGame()->getWindowSize();
  auto cameraPosition = gameObject->getGame()->getCameraPosition() - windowSize / 2;

  Bounds bounds = tileBounds;

  if (tile) {

    float distX = tileBounds.maxX - tileBounds.minX;
    float distY = tileBounds.maxY - tileBounds.minY;

    if (!(int) distX) {
      bounds.minX = (round(cameraPosition.x / tileSize.width) * tileSize.width) - 2 * tileSize.width;
      bounds.maxX = cameraPosition.x + windowSize.width + 2 * tileSize.width;
      distX = bounds.maxX - bounds.minX;
    }

    if (!(int) distY) {
      bounds.minY = (round(cameraPosition.y / tileSize.height) * tileSize.height) - 2 * tileSize.height;
      bounds.maxY = cameraPosition.y + windowSize.height + 2 * tileSize.height;
      distY = bounds.maxY - bounds.minY;
    }

    float countX = distX / tileSize.width;
    float countY = distY / tileSize.height;

    for (int x = 0; x < (int) countX; x++)
      for (int y = 0; y < (int) countY; y++)
        render(renderPosition.x + tileSize.width * (float) x, renderPosition.y + tileSize.height * (float) y);

    gameObject->setPosition({bounds.minX, bounds.minY});

    gameObject->setSize({round(countX) * tileSize.width, round(countY) * tileSize.height});

  } else {

    render(renderPosition.x, renderPosition.y);

  }

}

void TextureComponent::render(float x, float y) {

  Size size = gameObject->getSize();

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  SDL_Rect *srcRect = nullptr;
  SDL_FRect destRect;

  if (tile)
    destRect = {x, y, (float) width, (float) height};
  else
    destRect = {x, y, size.width, size.height};

  if (animated) {
    srcRect = new SDL_Rect{(int) tileSize.width * currentAnimationFrame + cropLeft, cropTop, (int) tileSize.width - cropRight, (int) tileSize.height - cropBottom};
    destRect = {x, y, (tileSize.width - (float) cropLeft - (float) cropRight) * scale,
                (tileSize.height - (float) cropTop - (float) cropBottom) * scale};
//    gameObject->setSize({destRect.w, destRect.h});
  }

  currentFrame++;
  if (currentFrame / animationFramesPerFrame == 1) {
    currentAnimationFrame++;
    currentFrame = 0;
  }

  if (currentAnimationFrame >= endFrame)
    currentAnimationFrame = startFrame;

  SDL_RenderCopyExF(renderer, texture, srcRect, &destRect, 0, nullptr,
                    gameObject->getFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

}

TextureComponent *TextureComponent::applyCrop(int left, int top, int right, int bottom) {
  cropLeft = left;
  cropTop = top;
  cropRight = right;
  cropBottom = bottom;

  return this;
}

TextureComponent *TextureComponent::setScale(float _scale) {
  this->scale = _scale;
  return this;
}

TextureComponent *TextureComponent::setFrameCount(int frames) {
  this->frameCount = frames;
  if (!endFrame)
    endFrame = frameCount;
  return this;
}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}



