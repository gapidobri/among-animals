#include <iostream>
#include <cmath>
#include "GameObject.h"
#include "../components/CameraComponent/CameraComponent.h"
#include "../components/PhysicsComponent/PhysicsComponent.h"
#include "../components/TextureComponent/TextureComponent.h"
#include "../components/PlayerComponent/PlayerComponent.h"

GameObject::GameObject() {
  position.x = 0;
  position.y = 0;
}

GameObject::GameObject(float x, float y) {
  position.x = x;
  position.y = y;
}

GameObject::~GameObject() {
  for (auto const &component : components) {
    delete component;
  }
}


void GameObject::registerComponent(Component *component) {
  component->gameObject = this;
  components.push_back(component);
}

void GameObject::setup() {
  if (record) {
    ofstream.open(strcat("gameobject_", name), std::ios::binary);
  }
  for (auto &component: components)
    component->setup();
}

void GameObject::loop() {
  for (auto &component: components)
    component->loop();

  // DEBUG

  SDL_SetRenderDrawColor(getRenderer(), 0, 255, 0, 255);
  SDL_FRect r{getRenderPosition().x, getRenderPosition().y, (float) size.width,
              (float) size.height};

//  SDL_RenderDrawRectF(getRenderer(), &r);

  // DEBUG
}


void GameObject::end() {
  for (auto &component: components)
    component->end();
}

Position GameObject::getPosition() {
  return position;

  float xOffset = anchorX == Anchor::Start ? 0 : size.width;
  float yOffset = anchorY == Anchor::Start ? 0 : size.height;

  return position - Position(xOffset, yOffset);
}

Position GameObject::getCenterPosition() {
  return position + Position(size.width / 2, size.height / 2);
}

void GameObject::setPosition(Position _position) {
  position = _position;
}

Position GameObject::getRenderPosition() {
  Position cameraPosition = game->getCameraPosition();
  Size windowSize = game->getWindowSize();
  float xOffset = anchorX == Anchor::Start ? 0 : size.width;
  float yOffset = anchorY == Anchor::Start ? 0 : size.height;
  return getPosition() - Position{xOffset, yOffset} - cameraPosition + windowSize / 2;
}

Game *GameObject::getGame() {
  return game;
}

void GameObject::templateFix() {
  // IDK, it doesn't work if I don't put that here ):
  getComponentOfType<CameraComponent>();
  getComponentOfType<PhysicsComponent>();
  getComponentOfType<CollisionComponent>();
  getComponentOfType<TextureComponent>();
  getComponentOfType<PlayerComponent>();
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

Bounds GameObject::getBounds(float inset) const {
  return {position.x + inset, position.x + size.width - inset, position.y + inset, position.y + size.height - inset};
}

GameObjectState GameObject::getState() {
  return state;
}

void GameObject::setState(GameObjectState _state) {
  state = _state;
}

void GameObject::setFlipped(bool flip) {
  this->flip = flip;
}

bool GameObject::getFlipped() {
  return flip;
}

GameObject *GameObject::setAnchor(Anchor x, Anchor y) {
  this->anchorX = x;
  this->anchorY = y;
  return this;
}

float GameObject::getDistanceTo(GameObject *gameObject) {
  auto distance = gameObject->position - position;
  return std::sqrtf(std::powf(distance.x, 2) + std::powf(distance.y, 2));
}

float GameObject::getAngleTo(GameObject *gameObject) {
  auto distance = gameObject->position - position;
  float x = distance.x, y = distance.y;
  float direction = 0;

  if (x > 0)
    direction = atanf(y / x);
  else if (x < 0)
    direction = atanf(y / x) + (float) M_PI;
  else if (y > 0)
    direction = M_PI / 2;
  else if (y < 0)
    direction = -M_PI / 2;

  return direction;
}

void GameObject::setHidden(bool hidden) {
  this->hidden = hidden;
}

bool GameObject::getHidden() {
  return hidden;
}

void GameObject::setRecord(bool record) {
  this->record = record;
}

void GameObject::setName(char *name) {
  this->name = name;
}

