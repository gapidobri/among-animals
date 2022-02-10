#include "BackgroundComponent.h"
#include <SDL2/SDL_image.h>
#include <iostream>

BackgroundComponent::BackgroundComponent(const char *filename) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
}

BackgroundComponent::BackgroundComponent(const char *filename, float z) {
  strcat(this->path, "../assets/");
  strcat(this->path, filename);
  this->z = z;
}

void BackgroundComponent::setup() {

  Component::setup();

  SDL_Renderer *renderer = getRenderer();
  texture = IMG_LoadTexture(renderer, path);

  if (!texture) {
    std::cout << "Texture load failed\n" << IMG_GetError() << '\n';
  }

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  Size window = gameObject->getGame()->getWindowSize();

  gameObject->setSize(Size{window.width, window.height});

}

void BackgroundComponent::loop() {

  Component::loop();

  auto position = gameObject->getRenderPosition();
  position.x *= z;
  auto size = gameObject->getSize();
  auto windowSize = gameObject->getGame()->getWindowSize();

  int xStartOffset = (int) (position.x / size.width + 1) * -1;
  int xEndOffset = (int) ((windowSize.width - position.x) / size.width + 1);

  for (int x = xStartOffset; x < xEndOffset; x++) {

    SDL_Rect rect{(int) (position.x + size.width * (float) x), (int) (position.y * z * 0.5) - 150, (int) (size.width + 1.2),
                  (int) (size.height + 1.2)};

    SDL_RenderCopy(getRenderer(), texture, nullptr, &rect);

  }

}

ComponentType BackgroundComponent::type() {
  return ComponentType::BackgroundComponent;
}