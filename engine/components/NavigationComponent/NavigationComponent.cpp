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

  // TODO: Check floor collision
  if (gameObject->getPosition().y >= 300 || collisionComponent->isColliding()) {
    if (keys[SDLK_SPACE])
      physicsComponent->setForceY(-15);
  }

  if (keys[SDLK_LEFT])
    physicsComponent->setForceX(-10);
  if (keys[SDLK_RIGHT])
    physicsComponent->setForceX(10);

}

ComponentType NavigationComponent::type() {
  return ComponentType::NavigationComponent;
}
