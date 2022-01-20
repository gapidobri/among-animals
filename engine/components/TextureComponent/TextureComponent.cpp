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

void TextureComponent::setup() {
  Component::setup();

  renderer = getRenderer();
  texture = IMG_LoadTexture(renderer, path);

  if (!texture) {
    std::cout << "Texture load failed\n" << IMG_GetError() << '\n';
  }

  Size size = gameObject->getSize();

  if (size.height == 0 && size.width == 0) {
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    gameObject->setSize(Size{width, height});
  }
}

void TextureComponent::loop() {

  Component::loop();

  auto position = gameObject->getRenderPosition();

  if (tile) {

    Size size = gameObject->getSize();

    int xStartOffset = (position.x / size.width + 1) * -1;
    int xEndOffset = ((1000 - position.x) / size.width + 1);

    int yStartOffset = (position.y / size.height + 1) * -1;
    int yEndOffset = ((650 - position.y) / size.height + 1);

    for (int x = xStartOffset; x < xEndOffset; x++)
      for (int y = yStartOffset; y < yEndOffset; y++)
        render(position.x + size.width * x, position.y + size.height * y);

  } else {

    render(position.x, position.y);

  }

}

void TextureComponent::render(int x, int y) {

  Size size = gameObject->getSize();

  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = size.width;
  rect.h = size.height;

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}


