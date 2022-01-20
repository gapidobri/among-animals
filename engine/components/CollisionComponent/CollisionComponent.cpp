#include "CollisionComponent.h"
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
  collisionsX.clear();
  collisionsY.clear();

  for (auto &object: gameObjects) {

    auto comp = object->getComponentOfType<CollisionComponent>();
    if (comp) {

      Position bp = object->getPosition();
      Size bs = object->getSize();

      bool collX = ap.x + as.width >= bp.x && bp.x + bs.width >= ap.x;
      bool collY = ap.y + as.height >= bp.y && bp.y + bs.height >= ap.y;

      if (collX && collY && object != gameObject) {
        collisions.push_back(object);

        Position depth = getCollisionDepth(object);
        if (depth.x != 0 && depth.y != 0) {
          if (std::abs(depth.x) < std::abs(depth.y))
            collisionsX.push_back(object);
          else
            collisionsY.push_back(object);
        }
      }

    }

  }
}



std::vector<GameObject *> CollisionComponent::getCollisions() {
  return collisions;
}

std::vector<GameObject *> CollisionComponent::getCollisions(Position offset) {
  std::vector<GameObject *> gameObjects = gameObject->getGame()->getGameObjects();

  Position ap = gameObject->getPosition() + offset;
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

Position CollisionComponent::getCollisionDepth(GameObject* target) {

  Position thisCenter = gameObject->getCenterPosition();
  Size thisHalfSize = gameObject->getSize() / 2;

  Position targetCenter = target->getCenterPosition();
  Size targetHalfSize = target->getSize() / 2;

  Position diff = thisCenter - targetCenter;
  Position minDist = thisHalfSize + targetHalfSize;
  Position depth = {diff.x > 0 ? minDist.x - diff.x : -minDist.x - diff.x,
                    diff.y > 0 ? minDist.y - diff.y : -minDist.y - diff.y};

  return {std::abs(depth.x), std::abs(depth.y)};

}

std::vector<GameObject *> CollisionComponent::getCollisionsX() {
  std::cout << collisionsX.size() << '\n';
  return collisionsX;
}

std::vector<GameObject *> CollisionComponent::getCollisionsY() {
  std::cout << collisionsY.size() << '\n';
  return collisionsY;
}

ComponentType CollisionComponent::type() {
  return ComponentType::CollisionComponent;
}