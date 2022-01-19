#pragma once

#include <SDL2/SDL.h>
#include "../GameObject/GameObject.h"

enum class ComponentType {
  Component,
  NavigationComponent,
  TextureComponent,
  FixedPositionComponent,
  CameraComponent,
  CollisionComponent,
  PhysicsComponent
};

class Component {

protected:
  GameObject *gameObject = nullptr;

  virtual void setup();

  virtual void loop();

  SDL_Renderer *getRenderer();

  friend class GameObject;

public:
  virtual ComponentType type();
};
