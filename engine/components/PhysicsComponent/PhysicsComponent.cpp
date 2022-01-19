#include "PhysicsComponent.h"
#include <cmath>
#include <iostream>
#include <iomanip>

void PhysicsComponent::setup() {
  Component::setup();
}

void PhysicsComponent::loop() {
  Component::loop();

  Position currPos = gameObject->getPosition();

  bool colliding = currPos.y >= 300 && prevPos.y <= 300;

  // Friction
  if (colliding)
    speed *= 0.7;

  double speedX = speed * std::cos(direction);
  double speedY = speed * std::sin(direction);

  // TODO: Temp collision
  // Bounce
  if (currPos.y >= 300 && prevPos.y <= 300)
    speedY *= -1;

  // Gravity
  // TODO: Check collisions
  if (!colliding)
    speedY += 0.5;

  speed = std::sqrt(std::pow(speedX, 2) + std::pow(speedY, 2));

  if (speed < 0.5)
    speed = 0;

  direction = calcDirection(speedX, speedY);

  prevPos = currPos;

  gameObject->setPosition(currPos + Position{(int) round(speedX), (int) round(speedY)});

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

ComponentType PhysicsComponent::type() {
  return ComponentType::PhysicsComponent;
}
