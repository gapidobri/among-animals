#include "CameraComponent.h"

void CameraComponent::setup() {
  Component::setup();
}

void CameraComponent::loop() {
  Component::loop();

  gameObject->getGame()->setCameraPosition(gameObject->getPosition());

}

ComponentType CameraComponent::type() {
  return ComponentType::CameraComponent;
}
