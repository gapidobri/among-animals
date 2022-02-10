#include "CollisionComponent.h"
#include <iostream>

void CollisionComponent::setup() {
  Component::setup();
}

void CollisionComponent::loop() {
  Component::loop();
}


std::vector<GameObject *> CollisionComponent::getCollisions() {
  return getCollisionsAfter({0, 0});
}

std::vector<GameObject *> CollisionComponent::getCollisionsAfter(Position force) {
  std::vector<GameObject *> gameObjects = gameObject->getGame()->getGameObjects();

  Position ap = gameObject->getPosition() + force;
  Size as = gameObject->getSize();

  std::vector<GameObject *> offCollisions;

  for (auto &object: gameObjects) {

    auto comp = object->getComponentOfType<CollisionComponent>();
    if (comp) {

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

bool CollisionComponent::isCollidingAfter(Position force) {
  return !getCollisionsAfter(force).empty();
}

Position CollisionComponent::getCollisionDepthAfter(GameObject *target, Position force) {

  Position thisCenter = gameObject->getCenterPosition() + force;
  Size thisHalfSize = gameObject->getSize() / 2.0;

  Position targetCenter = target->getCenterPosition();
  Size targetHalfSize = target->getSize() / 2.0;

  Position diff = thisCenter - targetCenter;
  Position minDist = thisHalfSize + targetHalfSize;
  Position depth = {diff.x > 0 ? minDist.x - diff.x : -minDist.x - diff.x,
                    diff.y > 0 ? minDist.y - diff.y : -minDist.y - diff.y};

  return {std::abs(depth.x), std::abs(depth.y)};

}

Position CollisionComponent::getCollisionDepth(GameObject *target) {

  return getCollisionDepthAfter(target, {0, 0});

}

ComponentType CollisionComponent::type() {
  return ComponentType::CollisionComponent;
}