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
  PhysicsComponent,
  TileComponent,
  BackgroundComponent,
  ProjectileComponent,
  PlayerComponent,
  MenuComponent,
};

class Component {

protected:
  GameObject *gameObject = nullptr;

  virtual void setup();
  virtual void loop();
  virtual void end();

  SDL_Renderer *getRenderer();

  friend class GameObject;

public:
  virtual ComponentType type();
};
