#pragma once

#include <vector>
#include <map>
#include <SDL2/SDL.h>
#include "../Size/Size.h"
#include "../Position/Position.h"

class GameObject;

class Game {

  SDL_Window *sdlWindow{};
  SDL_Renderer *sdlRenderer{};

  Size windowSize = {1000, 650};
  Position mousePosition;

  GameObject *camera{};
  std::vector<GameObject *> gameObjects;

  std::map<int, bool> keys;

  void setupGameObjects();

  void loopGameObjects();

  bool closeW = false;
  bool quit = false;
  bool isPaused = false;
  bool clean = false;

  void handleWindowEvent(SDL_Event);

  void handleKeyDownEvent(SDL_Event);

  void handleKeyUpEvent(SDL_Event);

  void handleMouseMotionEvent(SDL_Event event);

  SDL_Renderer *getRenderer();

public:

  Game();

  explicit Game(Size size);

  std::function<void()> onEndLevelCallback;

  void start();

  void pause();

  void resume();

  void end(bool exit);

  void removeAllGameObjects();

  void registerGameObject(GameObject *);

  void removeGameObject(GameObject *);

  void onEndLevel(std::function<void()> callback);

  Position getCameraPosition();

  void setCameraPosition(Position position);

  Position getMousePosition();

  bool getKey(int);

  std::map<int, bool> getKeys();

  std::vector<GameObject *> getGameObjects();

  Size getWindowSize();

  friend class GameObject;

};
