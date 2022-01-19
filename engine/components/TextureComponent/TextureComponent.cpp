#include "TextureComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

TextureComponent::TextureComponent(const char *filename) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
}


void TextureComponent::setup() {

  Component::setup();

  renderer = getRenderer();

  texture = IMG_LoadTexture(renderer, path);

  if (!texture) {
    std::cout << "Texture load failed\n" << IMG_GetError() << '\n';
  }

}

void TextureComponent::loop() {

  Component::loop();

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  auto position = gameObject->getRenderPosition();

  Size size = gameObject->getSize();

  SDL_Rect rect;
  rect.x = position.x;
  rect.y = position.y;

  if (size.height == 0 && size.width == 0) {
    rect.w = width / 10;
    rect.h = height / 10;
  } else {
    rect.w = width;
    rect.h = height;
  }


//  gameObject->setSize(Size(rect));

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}

