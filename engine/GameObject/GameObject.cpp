#include <iostream>
#include "GameObject.h"
#include "../components/CameraComponent/CameraComponent.h"
#include "../components/PhysicsComponent/PhysicsComponent.h"

GameObject::GameObject() {
  position.x = 0;
  position.y = 0;
}

GameObject::GameObject(int x, int y) {
  position.x = x;
  position.y = y;
}

void GameObject::registerComponent(Component *component) {
  component->gameObject = this;
  components.push_back(component);
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

Position GameObject::getCenterPosition() {
  return position + Position(size.width / 2, size.height / 2);
}

void GameObject::setPosition(Position _position) {
  position = _position;
}

Position GameObject::getRenderPosition() {
  Position cameraPosition = game->getCameraPosition();
  return position - cameraPosition + Position{500, 325};
}

Game *GameObject::getGame() {
  return game;
}

void GameObject::templateFix() {
  // IDK, it doesn't work if I don't put that here ):
  getComponentOfType<CameraComponent>();
  getComponentOfType<PhysicsComponent>();
  getComponentOfType<CollisionComponent>();
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

std::vector<Component *> GameObject::getComponents() {
  return components;
}

Size GameObject::getSize() {
  return size;
}

void GameObject::setSize(Size _size) {
  size = _size;
}

Bounds GameObject::getBounds(int inset) const {
  return {position.x + inset, position.x + size.width - inset, position.y + inset, position.y + size.height - inset};
}




