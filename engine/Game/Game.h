#pragma once

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "../Position/Position.h"

class GameObject;

class Game {

  SDL_Window *sdlWindow;
  SDL_Renderer *sdlRenderer;

  GameObject *camera;
  std::vector<GameObject *> gameObjects;

  std::map<int, bool> keys;

  void setupGameObjects();

  void loopGameObjects();

  bool quit;

  void handleWindowEvent(SDL_Event);
  void handleKeyDownEvent(SDL_Event);
  void handleKeyUpEvent(SDL_Event);

  SDL_Renderer *getRenderer();

public:

  void start();

  void registerGameObject(GameObject *);
  void registerCamera(GameObject *);

  Position getCameraPosition();
  void setCameraPosition(Position position);

  bool getKey(int);
  std::map<int, bool> getKeys();

  std::vector<GameObject *> getGameObjects();

  friend class GameObject;

};
