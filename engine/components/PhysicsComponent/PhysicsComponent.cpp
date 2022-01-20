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

  bool isColliding = collisionComponent != nullptr && collisionComponent->isColliding();

  // Apply friction if object is colliding
  if (isColliding)
    speed *= 0.9;

  double speedX = speed * std::cos(direction);
  double speedY = speed * std::sin(direction);

  std::vector<GameObject *> collisions;
  if (collisionComponent) {
    collisions = collisionComponent->getCollisions(Position{(int) speedX, (int) speedY});
    isColliding = !collisions.empty();
  }

  // Remove speed if to low
//  if (speedX < 0.3 && speedX > -0.3)
//    speedX = 0;
//
//  if (speedY < 0.3 && speedY > -0.3)
//    speedY = 0;

  if (isColliding && collisionComponent) {

    for (auto &collision: collisions) {
      double calcBounce = bounciness / 2;
      auto *physicsComponent = collision->getComponentOfType<PhysicsComponent>();
      if (physicsComponent)
        calcBounce = (bounciness + physicsComponent->bounciness) / 2;

      Position depth = collisionComponent->getCollisionDepth(collision);

      if (depth.x < depth.y)
        speedX *= -calcBounce;
      else {
        speedY *= -calcBounce;
        speedY -= 0.6;
      }
    }

  }

  // Gravity
  speedY += 0.6;

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));

  std::cout << speedY << '\n';

  if (speedY == 0) {

    SDL_Rect rect{100, 100, 100, 100};
    SDL_RenderFillRect(getRenderer(), &rect);

  }

  direction = calcDirection(speedX, speedY);

  // DEBUG >>

  Position renderPosition = gameObject->getRenderPosition();

  SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);

  SDL_RenderDrawLineF(getRenderer(), (float) renderPosition.x, (float) renderPosition.y,
                      (float) (renderPosition.x + 5 * speedX), (float) (renderPosition.y + 5 * speedY));

  // >> DEBUG

  gameObject->setPosition(position + Position((int) round(speedX), (int) round(speedY)));

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

void PhysicsComponent::setForceX(double speedX) {

  double speedY = speed * std::sin(direction);

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

void PhysicsComponent::setForceY(double speedY) {

  double speedX = speed * std::cos(direction);

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

ComponentType PhysicsComponent::type() {
  return ComponentType::PhysicsComponent;
}