#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../Game/Game.h"
#include "../Component/Component.h"
#include "../Size/Size.h"
#include "../Bounds/Bounds.h"

enum GameObjectState {
  Idle,
  Moving,
  JumpingStart,
  Jumping,
  FallingStart,
  Falling,
};

class Component;

class GameObject {

  void templateFix();

protected:
  Position position;
  Size size;

  GameObjectState state = GameObjectState::Idle;

  Game *game = nullptr;
  std::vector<Component *> components;

  void setup();

  void loop();

  SDL_Renderer *getRenderer();

public:
  GameObject();

  GameObject(float, float);

  template<typename T>
  T *getComponentOfType();

  Position getPosition();

  Position getCenterPosition();

  Position getRenderPosition();

  void setPosition(Position);

  Size getSize();

  void setSize(Size);

  Bounds getBounds(float inset) const;

  Game *getGame();

  void registerComponent(Component *);

  std::vector<Component *> getComponents();

  GameObjectState getState();

  void setState(GameObjectState state);

  friend class Game;

  friend class Component;

};
