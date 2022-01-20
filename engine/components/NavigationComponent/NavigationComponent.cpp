#include "NavigationComponent.h"

void NavigationComponent::setup() {
  Component::setup();

  physicsComponent = gameObject->getComponentOfType<PhysicsComponent>();
  collisionComponent = gameObject->getComponentOfType<CollisionComponent>();

}

void NavigationComponent::loop() {
  Component::loop();

  Game *game = gameObject->getGame();
  std::map<int, bool> keys = game->getKeys();

  // TODO: Fix collision when bounciness > 0
  if (collisionComponent->isColliding()) {
    if (keys[SDLK_SPACE]) {
      physicsComponent->setSpeedY(-15);
    }
  }

  if (keys[SDLK_LEFT])
    physicsComponent->setSpeedX(-10);
  if (keys[SDLK_RIGHT])
    physicsComponent->setSpeedX(10);

}

ComponentType NavigationComponent::type() {
  return ComponentType::NavigationComponent;
}
