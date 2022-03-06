
#include "ProjectileComponent.h"

void ProjectileComponent::setup() {
  Component::setup();

  position = gameObject->getRenderPosition();
}

void ProjectileComponent::loop() {
  Component::loop();

  SDL_FRect r{position.x, position.y, 10.0, 10.0};

  SDL_RenderDrawRectF(getRenderer(), &r);
}

ComponentType ProjectileComponent::type() {
  return ComponentType::ProjectileComponent;
}
