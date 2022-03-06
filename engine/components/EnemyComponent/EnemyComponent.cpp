#include <iostream>
#include "EnemyComponent.h"

void EnemyComponent::setup() {
  Component::setup();

  availableStates.push_back(Idle);
  availableStates.push_back(Moving);

  collisionComponent = gameObject->getComponentOfType<CollisionComponent>();
  targetPlayerComponent = target->getComponentOfType<PlayerComponent>();
}

void EnemyComponent::loop() {
  Component::loop();

  auto collisions = collisionComponent->getCollisions();
  bool isColliding = std::find(collisions.begin(), collisions.end(), target) != collisions.end();
  if (isColliding) {
    targetPlayerComponent->damage();
  }

  auto currentState = gameObject->getState();

  // Check if new state needed
  if (nextState == 0) {
    // Set random state
    auto randomState = getRandomState();
    gameObject->setState(randomState);

    if (randomState == Moving) {
      movementSpeed = (float) (random() % 10) - 5;
      gameObject->setFlipped(movementSpeed < 0);
    }

    // Set random state timeout
    nextState = (int) random() % 300;
  }

  float targetDistance = gameObject->getDistanceTo(target);
  if (targetDistance < 500 && targetDistance > 100) {
    gameObject->setState(Moving);
    if (gameObject->getAngleTo(target) > 0) {
      gameObject->setFlipped(true);
      movementSpeed = -7;
    } else {
      gameObject->setFlipped(false);
      movementSpeed = 7;
    }
  }

  if (currentState == Moving) {
    auto position = gameObject->getPosition();
    gameObject->setPosition({position.x + movementSpeed, position.y});
  }

  nextState--;

}

GameObjectState EnemyComponent::getRandomState() {
  int selected = (int) (random() % availableStates.size());
  return availableStates.at(selected);
}

void EnemyComponent::setTarget(GameObject *_target) {
  target = _target;
}