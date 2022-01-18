#include "Component.h"

void Component::setup() {

}

void Component::loop() {

}

ComponentType Component::type() {
  return ComponentType::Component;
}

SDL_Renderer *Component::getRenderer() {
  return gameObject->getRenderer();
}
