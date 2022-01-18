#include "FixedPositionComponent.h"

FixedPositionComponent::FixedPositionComponent(int x, int y) {
  position.x = x;
  position.y = y;
}

void FixedPositionComponent::setup() {
  Component::setup();
}

void FixedPositionComponent::loop() {
  Component::loop();
  Position cameraPosition = gameObject->getGame()->getCameraPosition();
  Position newPosition{cameraPosition.x + position.x, cameraPosition.y + position.y};
  gameObject->setPosition(newPosition);
}

ComponentType FixedPositionComponent::type() {
  return ComponentType::FixedPositionComponent;
}
