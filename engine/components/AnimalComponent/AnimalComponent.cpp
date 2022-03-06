#include <iostream>
#include "AnimalComponent.h"

void AnimalComponent::setup() {
  Component::setup();

  collisionComponent = gameObject->getComponentOfType<CollisionComponent>();
  playerComponent = player->getComponentOfType<PlayerComponent>();
}

void AnimalComponent::loop() {
  Component::loop();

  renderProgress();

  auto collisions = collisionComponent->getCollisions();

  bool isColliding = std::find(collisions.begin(), collisions.end(), player) != collisions.end();

  if (isColliding) {

    captureProgress += 0.01;

    if (captureProgress >= 1.0) {
      playerComponent->animalCollected();
      gameObject->getGame()->removeGameObject(gameObject);
    }

  }

}

void AnimalComponent::renderProgress() {

  if (captureProgress == 0) return;

  auto renderPosition = gameObject->getRenderPosition();

  SDL_FRect progRect = SDL_FRect{renderPosition.x, renderPosition.y, 50 * captureProgress, 5};
  SDL_FRect endRect = SDL_FRect{renderPosition.x, renderPosition.y, 50, 5};

  SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 0);
  SDL_RenderFillRectF(getRenderer(), &progRect);
  SDL_RenderDrawRectF(getRenderer(), &endRect);
}

void AnimalComponent::setPlayer(GameObject *player) {
  this->player = player;
}

