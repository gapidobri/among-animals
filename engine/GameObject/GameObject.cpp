#include <iostream>
#include "GameObject.h"
#include "../components/CameraComponent/CameraComponent.h"

GameObject::GameObject() {
  position.x = 0;
  position.y = 0;
}

GameObject::GameObject(int x, int y) {
  position.x = x;
  position.y = y;
}

void GameObject::registerComponent(Component *component) {
  components.push_back(component);
  component->gameObject = this;
}

void GameObject::setup() {
  for (auto &component: components)
    component->setup();
}

void GameObject::loop() {
  for (auto &component: components)
    component->loop();
}

Position GameObject::getPosition() {
  return position;
}

void GameObject::setPosition(Position _position) {
  position = _position;
}

Position GameObject::getRenderPosition() {
  Position cameraPosition = game->getCameraPosition();
  return Position{position.x - cameraPosition.x, position.y - cameraPosition.y};
}

Game *GameObject::getGame() {
  return game;
}

void GameObject::templateFix() {
  // IDK, it doesn't work if I don't put that here ):
  getComponentOfType<CameraComponent>();
}

SDL_Renderer *GameObject::getRenderer() {
  return game->getRenderer();
}

template<typename T>
T *GameObject::getComponentOfType() {
  for (auto &component: components) {
    T t;
    if (component->type() == dynamic_cast<Component &>(t).type())
      return dynamic_cast<T *>(component);
  }
  return nullptr;
}

Size GameObject::getSize() {
  return size;
}

void GameObject::setSize(Size _size) {
  size = _size;
}




