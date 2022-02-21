#include "TextureComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TextureComponent::TextureComponent() = default;

TextureComponent::TextureComponent(const char *filename) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
}

TextureComponent::TextureComponent(const char *filename, int scale, bool animated, GameObjectState state) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->animated = animated;
  this->state = state;
}

TextureComponent::TextureComponent(const char *filename, int scale, bool animated, GameObjectState state,
                                   int startFrame, int endFrame) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->animated = animated;
  this->state = state;
  this->startFrame = startFrame;
  this->endFrame = endFrame;
}

TextureComponent::TextureComponent(const char *filename, int scale, Bounds tileBounds) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->tile = true;
  this->tileBounds = tileBounds;
}

TextureComponent::TextureComponent(const char *filename, int scale, Position position, Size size) {
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

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  if (!tile) {
    gameObject->setSize({height * scale, height * scale});
  }

  if (animated && startFrame == 0 && endFrame == 0) {
    endFrame = (int) (width / height);
  }

  tileSize = {width, height};
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

    for (int x = 0; x < (int) countX; x++) {
      for (int y = 0; y < (int) countY; y++) {
        render(renderPosition.x + tileSize.width * (float) x, renderPosition.y + tileSize.height * (float) y);
      }
    }

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
    srcRect = new SDL_Rect{48 * currentAnimationFrame, 16, 32, 32};
    destRect = {x, y, size.width, size.height};
  }

  currentFrame++;
  if (currentFrame / animationFramesPerFrame == 1) {
    currentAnimationFrame++;
    currentFrame = 0;
  }

  if (currentAnimationFrame >= endFrame)
    currentAnimationFrame = startFrame;

  SDL_RenderCopyExF(renderer, texture, srcRect, &destRect, 0, nullptr,  gameObject->getFlipped() ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}


