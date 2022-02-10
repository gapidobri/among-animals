#include "PhysicsComponent.h"
#include <cmath>

PhysicsComponent::PhysicsComponent() = default;

PhysicsComponent::PhysicsComponent(float bounciness) {
  this->bounciness = bounciness;
}

PhysicsComponent::PhysicsComponent(bool dynamic) {
  this->dynamic = dynamic;
}

PhysicsComponent::PhysicsComponent(bool dynamic, float bounciness) {
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

  float speedX = speed * std::cos(direction);
  float speedY = speed * std::sin(direction);

  // Gravity
  speedY += 0.6;

  std::vector<GameObject *> collisions;
  bool isColliding = false;
  if (collisionComponent) {
    collisions = collisionComponent->getCollisionsAfter({speedX, speedY});
    isColliding = !collisions.empty();
  }

  Position collisionDepth;

  if (isColliding) {
    speedX *= 0.9;

    for (auto &collision: collisions) {

      float calcBounce = bounciness / 2;
      auto *physicsComponent = collision->getComponentOfType<PhysicsComponent>();
      if (physicsComponent)
        calcBounce = (bounciness + physicsComponent->bounciness) / 2;

      Position depth = collisionComponent->getCollisionDepth(collision);

      if (depth.x < depth.y)
        speedX *= -calcBounce;
      else {
        if (calcBounce == 0.0) {
          collisionDepth = collisionComponent->getCollisionDepthAfter(collision, {speedX, speedY});
          if (speedY < 0) {
            collisionDepth.y += 1.0;
            collisionDepth.y *= -1.0;
          }
        } else {
          speedY *= -calcBounce;
          speedY += 0.6;
        }
      }
    }
  }

  if (!isColliding) {

    if (speedY < -10)
      gameObject->setState(GameObjectState::JumpingStart);
    else if (speedY <= 0)
      gameObject->setState(GameObjectState::Jumping);
    else if (speedY > 0)
      gameObject->setState(GameObjectState::FallingStart);
    else if (speedY > 20)
      gameObject->setState(GameObjectState::Falling);
  }

  speedY -= collisionDepth.y;

  position += Position(speedX, speedY);

  speed = std::sqrtf(std::powf(speedX, 2) + std::powf(speedY, 2));

  direction = calcDirection(speedX, speedY);

  gameObject->setPosition(position);

  // DEBUG

  Position renderPosition = gameObject->getRenderPosition();

  SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);

  SDL_RenderDrawLineF(getRenderer(), (float) renderPosition.x, (float) renderPosition.y,
                      (float) (renderPosition.x + 5 * speedX), (float) (renderPosition.y + 5 * speedY));

  // DEBUG

}

float PhysicsComponent::calcDirection(float x, float y) {
  if (x > 0)
    return atanf(y / x);
  if (x < 0)
    return atanf(y / x) + (float) M_PI;
  if (y > 0)
    return M_PI / 2;
  if (y < 0)
    return -M_PI / 2;
  return 0;
}

void PhysicsComponent::applyForce(float _direction, float _speed) {

  float addSpeedX = _speed * std::cos(_direction);
  float addSpeedY = _speed * std::sin(_direction);

  float speedX = speed * std::cos(direction);
  float speedY = speed * std::sin(direction);

  speedX += addSpeedX;
  speedY -= addSpeedY;

  speed = std::sqrtf(std::powf(speedX, 2) + std::powf(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

void PhysicsComponent::setSpeedX(float speedX) {

  float speedY = speed * std::sin(direction);

  speed = std::sqrtf(std::powf(speedX, 2) + std::powf(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

void PhysicsComponent::setSpeedY(float speedY) {

  float speedX = speed * std::cos(direction);

  speed = std::sqrtf(std::powf(speedX, 2) + std::powf(speedY, 2));
  direction = calcDirection(speedX, speedY);

}

ComponentType PhysicsComponent::type() {
  return ComponentType::PhysicsComponent;
}