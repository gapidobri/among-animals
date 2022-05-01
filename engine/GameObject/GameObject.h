#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "../Game/Game.h"
#include "../Component/Component.h"
#include "../Size/Size.h"
#include "../Bounds/Bounds.h"
#include <fstream>

enum GameObjectState {
  Idle,
  Moving,
  JumpingStart,
  Jumping,
  FallingStart,
  Falling,
};

enum Anchor {
  Start,
  End,
};

class Component;

class GameObject {

  void templateFix();

protected:
  Position position;
  Anchor anchorX = Anchor::Start, anchorY = Anchor::Start;

  Size size;
  bool flip = false, hidden = false;

  GameObjectState state = GameObjectState::Idle;

  Game *game = nullptr;
  std::vector<Component *> components;

  bool record = false;

  char *name{};
  std::ofstream ofstream;
  std::ifstream ifstream;

  void setup();
  void loop();
  void end();

  SDL_Renderer *getRenderer();

public:
  GameObject();

  GameObject(float, float);

  ~GameObject();

  template<typename T>
  T *getComponentOfType();

  Position getPosition();

  Position getCenterPosition();

  Position getRenderPosition();

  void setPosition(Position);

  Size getSize();

  void setSize(Size);

  void setFlipped(bool flip);
  bool getFlipped();

  Bounds getBounds(float inset) const;

  Game *getGame();

  void registerComponent(Component *);

  void removeComponent(Component *);

  std::vector<Component *> getComponents();

  GameObjectState getState();

  void setState(GameObjectState state);

  GameObject *setAnchor(Anchor x, Anchor y);

  float getDistanceTo(GameObject *gameObject);

  float getAngleTo(GameObject *gameObject);

  void setHidden(bool hidden);
  bool getHidden();

  void setName(char *name);
  void setRecord(bool record);

  friend class Game;

  friend class Component;

};
