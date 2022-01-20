#include "PhysicsComponent.h"
#include <cmath>
#include <iostream>

PhysicsComponent::PhysicsComponent() = default;

PhysicsComponent::PhysicsComponent(double bounciness) {
  this->bounciness = bounciness;
}

PhysicsComponent::PhysicsComponent(bool dynamic) {
  this->dynamic = dynamic;
}

PhysicsComponent::PhysicsComponent(bool dynamic, double bounciness) {
  this->bounciness = bounciness;
  this->dynamic = dynamic;
}


void PhysicsComponent::setup() {
  Component::setup();

  collisionComponent = gameObject->getComponentOfType<CollisionComponent>();
}

void PhysicsComponent::loop() {
  Component::loop();

  if (!dynamic) return;

  Position position = gameObject->getPosition();

  double speedX = speed * std::cos(direction);
  double speedY = speed * std::sin(direction);

  // Gravity
  speedY += 0.6;

  std::vector<GameObject *> collisions;
  bool isColliding = false;
  if (collisionComponent) {
    collisions = collisionComponent->getCollisionsAfter({(int) speedX, (int) speedY});
    isColliding = !collisions.empty();
  }

  Position collisionDepth;

  if (isColliding) {
    speedX *= 0.9;

    for (auto &collision: collisions) {

      double calcBounce = bounciness / 2;
      auto *physicsComponent = collision->getComponentOfType<PhysicsComponent>();
      if (physicsComponent)
        calcBounce = (bounciness + physicsComponent->bounciness) / 2;

      Position depth = collisionComponent->getCollisionDepth(collision);

      if (depth.x < depth.y)
        speedX *= -calcBounce;
      else {
        if (calcBounce == 0.0)
          collisionDepth = collisionComponent->getCollisionDepthAfter(collision, {(int) speedX, (int) speedY});
        else {
          speedY *= -calcBounce;
          speedY += 0.6;
        }
      }

    }

  }

  speedY -= collisionDepth.y;

  position += Position((int) speedX, (int) speedY);

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));

  direction = calcDirection(speedX, speedY);

  gameObject->setPosition(position);

  // DEBUG

  Position renderPosition = gameObject->getRenderPosition();

  SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);

  SDL_RenderDrawLineF(getRenderer(), (float) renderPosition.x, (float) renderPosition.y,
                      (float) (renderPosition.x + 5 * speedX), (float) (renderPosition.y + 5 * speedY));

  // DEBUG

}

double PhysicsComponent::calcDirection(double x, double y) {
  if (x > 0)
    return atan(y / x);
  if (x < 0)
    return atan(y / x) + M_PI;
  if (y > 0)
    return M_PI / 2;
  if (y < 0)
    return -M_PI / 2;
  return 0;
}

void PhysicsComponent::applyForce(double _direction, double _speed) {

  double addSpeedX = _speed * std::cos(_direction);
  double addSpeedY = _speed * std::sin(_direction);

  double speedX = speed * std::cos(direction);
  double speedY = speed * std::sin(direction);

  speedX += addSpeedX;
  speedY -= addSpeedY;

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

void PhysicsComponent::setSpeedX(double speedX) {

  double speedY = speed * std::sin(direction);

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

void PhysicsComponent::setSpeedY(double speedY) {

  double speedX = speed * std::cos(direction);

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

ComponentType PhysicsComponent::type() {
  return ComponentType::PhysicsComponent;
}