#include "TextureComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TextureComponent::TextureComponent(const char *filename) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
}

TextureComponent::TextureComponent(const char *filename, bool tile) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->tile = tile;
}

TextureComponent::TextureComponent(const char *filename, int scale, bool tile) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->scale = scale;
  this->tile = tile;
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

  if (!tile)
    gameObject->setSize({width * scale, height * scale});

  tileSize = {width, height};
}

void TextureComponent::loop() {

  Component::loop();

  auto renderPosition = gameObject->getRenderPosition();
  auto windowSize = gameObject->getGame()->getWindowSize();
  auto cameraPosition = gameObject->getGame()->getCameraPosition() - windowSize / 2;

  Bounds bounds = tileBounds;

  if (tile) {

    int distX = tileBounds.maxX - tileBounds.minX;
    int distY = tileBounds.maxY - tileBounds.minY;

    if (!distX) {
      bounds.minX = (cameraPosition.x / tileSize.width * tileSize.width) - 2 * tileSize.width;
      bounds.maxX = cameraPosition.x + windowSize.width + 2 * tileSize.width;
      distX = bounds.maxX - bounds.minX;
    }

    if (!distY) {
      bounds.minY = (cameraPosition.y / tileSize.height * tileSize.height) - 2 * tileSize.height;
      bounds.maxY = cameraPosition.y + windowSize.height + 2 * tileSize.height;
      distY = bounds.maxY - bounds.minY;
    }

    int countX = distX / tileSize.width;
    int countY = distY / tileSize.height;

    for (int x = 0; x < countX; x++) {
      for (int y = 0; y < countY; y++) {
        render(renderPosition.x + tileSize.width * x, renderPosition.y + tileSize.height * y);
      }
    }

    gameObject->setPosition({bounds.minX, bounds.minY});
    gameObject->setSize({countX * tileSize.width, countY * tileSize.height});

  } else {

    render(renderPosition.x, renderPosition.y);

  }

}

void TextureComponent::render(int x, int y) {

  Size size = gameObject->getSize();

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  SDL_Rect rect;

  if (tile)
    rect = {x, y, width, height};
  else
    rect = {x, y, size.width, size.height};

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}


