#include "Component.h"
#include <iostream>

void Component::setup() {

}

void Component::loop() {
  
}

void Component::end() {

}


ComponentType Component::type() {
  return ComponentType::Component;
}

SDL_Renderer *Component::getRenderer() {
  return gameObject->getRenderer();
}

