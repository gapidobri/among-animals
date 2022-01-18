#include "TextureComponent.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

void TextureComponent::setup() {

  Component::setup();

  renderer = getRenderer();

  texture = IMG_LoadTexture(renderer, "../assets/aiken.png");

  if (!texture) {
    std::cout << "Texture load failed\n" << IMG_GetError() << '\n';
  }

}

void TextureComponent::loop() {

  Component::loop();

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  auto position = gameObject->getRenderPosition();

  SDL_Rect rect;
  rect.x = position.x;
  rect.y = position.y;
  rect.w = width / 10;
  rect.h = height / 10;

  gameObject->setSize(Size(rect));

  SDL_RenderCopy(renderer, texture, nullptr, &rect);

}

ComponentType TextureComponent::type() {
  return ComponentType::TextureComponent;
}
