#include "CameraComponent.h"

void CameraComponent::setup() {
  Component::setup();
}

void CameraComponent::loop() {

  Component::loop();

}

ComponentType CameraComponent::type() {
  return ComponentType::CameraComponent;
}
