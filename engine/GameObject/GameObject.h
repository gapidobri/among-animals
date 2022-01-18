#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../Game/Game.h"
#include "../Position/Position.h"
#include "../Component/Component.h"
#include "../Size/Size.h"

class Component;

class GameObject {

private:
  void templateFix();

protected:
  Position position;
  Size size;

  Game *game = nullptr;
  std::vector<Component *> components;

  void setup();

  void loop();

  SDL_Renderer *getRenderer();

public:
  GameObject();
  GameObject(int, int);

  template<typename T>
  T *getComponentOfType();

  Position getPosition();

  Position getRenderPosition();

  void setPosition(Position);

  Size getSize();

  void setSize(Size);

  Game *getGame();

  void registerComponent(Component *);

  friend class Game;

  friend class Component;

};
