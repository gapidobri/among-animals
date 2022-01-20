#include "CollisionComponent.h"
#include "../CameraComponent/CameraComponent.h"
#include <iostream>

void CollisionComponent::setup() {
  Component::setup();
}

void CollisionComponent::loop() {
  Component::loop();

  std::vector<GameObject *> gameObjects = gameObject->getGame()->getGameObjects();

  Position ap = gameObject->getPosition();
  Size as = gameObject->getSize();

  collisions.clear();

  for (auto object: gameObjects) {

    auto comp = object->getComponentOfType<CollisionComponent>();
    auto tmp = object->getComponentOfType<CameraComponent>();
    if (comp && !tmp) {

      Position bp = object->getPosition();
      Size bs = object->getSize();

      bool collX = ap.x + as.width >= bp.x && bp.x + bs.width >= ap.x;
      bool collY = ap.y + as.height >= bp.y && bp.y + bs.height >= ap.y;

      if (collX && collY && object != gameObject)
        collisions.push_back(object);

    }


  }

}

ComponentType CollisionComponent::type() {
  return ComponentType::CollisionComponent;
}

std::vector<GameObject *> CollisionComponent::getCollisions() {
  return collisions;
}

std::vector<GameObject *> CollisionComponent::getCollisions(Position offset) {
  std::vector<GameObject *> gameObjects = gameObject->getGame()->getGameObjects();

  Position ap = gameObject->getPosition() + offset;
  Size as = gameObject->getSize();

  std::vector<GameObject *> offCollisions;

  for (auto object: gameObjects) {

    auto comp = object->getComponentOfType<CollisionComponent>();
    auto tmp = object->getComponentOfType<CameraComponent>();
    if (comp && !tmp) {

      Position bp = object->getPosition();
      Size bs = object->getSize();

      bool collX = ap.x + as.width >= bp.x && bp.x + bs.width >= ap.x;
      bool collY = ap.y + as.height >= bp.y && bp.y + bs.height >= ap.y;

      if (collX && collY && object != gameObject)
        offCollisions.push_back(object);

    }

  }

  return offCollisions;

}

bool CollisionComponent::isColliding() {
  return !getCollisions().empty();
}

bool CollisionComponent::isColliding(Position offset) {
  return !getCollisions(offset).empty();
}

