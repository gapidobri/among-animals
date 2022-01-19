#include "CollisionComponent.h"

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
    Position bp = object->getPosition();
    Size bs = object->getSize();

    bool collX = ap.x + as.width >= bp.x && bp.x + bs.width >= ap.x;
    bool collY = ap.y + as.height >= bp.y && bp.y + bs.height >= ap.y;

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
