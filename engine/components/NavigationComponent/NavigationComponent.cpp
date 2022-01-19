#include "NavigationComponent.h"

void NavigationComponent::setup() {
  Component::setup();
}

void NavigationComponent::loop() {
  Component::loop();

  Game *game = gameObject->getGame();
  std::map<int, bool> keys = game->getKeys();
  Position position = gameObject->getPosition();

  if (keys[SDLK_LEFT])
    position.x -= 5;
  if (keys[SDLK_RIGHT])
    position.x += 5;
  if (keys[SDLK_UP])
    position.y -= 5;
  if (keys[SDLK_DOWN])
    position.y += 5;

  gameObject->setPosition(position);

}

ComponentType NavigationComponent::type() {
  return ComponentType::NavigationComponent;
}
