#include "NavigationComponent.h"

void NavigationComponent::setup() {
  Component::setup();

  physicsComponent = gameObject->getComponentOfType<PhysicsComponent>();
  collisionComponent = gameObject->getComponentOfType<CollisionComponent>();
  textureComponent = gameObject->getComponentOfType<TextureComponent>();

}

void NavigationComponent::loop() {
  Component::loop();

  Game *game = gameObject->getGame();
  std::map<int, bool> keys = game->getKeys();

  gameObject->setState(GameObjectState::Idle);

  // TODO: Fix collision when bounciness > 0
  if (collisionComponent->isColliding()) {
    if (keys[SDLK_SPACE]) {
      physicsComponent->setSpeedY(-15);
    }
  }

  if (keys[SDLK_LEFT]) {
    physicsComponent->setSpeedX(-10);
    gameObject->setState(GameObjectState::Moving);
    gameObject->setFlipped(true);
  }
  if (keys[SDLK_RIGHT]) {
    physicsComponent->setSpeedX(10);
    gameObject->setState(GameObjectState::Moving);
    gameObject->setFlipped(false);
  }

}

ComponentType NavigationComponent::type() {
  return ComponentType::NavigationComponent;
}
