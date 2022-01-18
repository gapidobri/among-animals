#include <iostream>
#include "CollisionComponent.h"

void CollisionComponent::setup() {
  Component::setup();
}

void CollisionComponent::loop() {
  Component::loop();

  std::vector<GameObject *> gameObjects = gameObject->getGame()->getGameObjects();

  Position a = gameObject->getPosition();
  Size as = gameObject->getSize();

  collisions.clear();

  for (auto object: gameObjects) {
    Position b = object->getPosition();
    Size bs = object->getSize();

    bool collX = a.x + as.width >= b.x && b.x + bs.width >= a.x;
    bool collY = a.y + as.height >= b.y && b.y + bs.height >= a.y;

    if (collX && collY && object != gameObject)
      collisions.push_back(object);

  }

}

ComponentType CollisionComponent::type() {
  return ComponentType::CollisionComponent;
}

std::vector<GameObject *> CollisionComponent::getCollisions() {
  return collisions;
}
