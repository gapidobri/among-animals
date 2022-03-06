#include <iostream>
#include "Game.h"
#include "../GameObject/GameObject.h"
#include "../components/CameraComponent/CameraComponent.h"
#include <SDL2/SDL_ttf.h>
#include <sstream>

Game::Game() = default;

Game::Game(Size size) {
  this->windowSize = size;
}

void Game::start() {

  if (camera == nullptr) {
    std::cout << "No camera component found\n";
    exit(1);
  }

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();

  // Create Window
  sdlWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int) windowSize.width,
                               (int) windowSize.height, SDL_WINDOW_OPENGL);

  // Create Renderer
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
  SDL_RenderClear(sdlRenderer);
  SDL_RenderPresent(sdlRenderer);

  setupGameObjects();

  quit = false;
  SDL_Event event;

  Uint32 a, b, delta;

  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {

        case SDL_WINDOWEVENT:
          handleWindowEvent(event);
          break;

        case SDL_KEYDOWN:
          handleKeyDownEvent(event);
          break;

        case SDL_KEYUP:
          handleKeyUpEvent(event);
          break;

        case SDL_MOUSEMOTION:
          handleMouseMotionEvent(event);
          break;

      }
    }

    a = SDL_GetTicks();
    delta = a - b;

    if (delta > 1000 / 60.0) {

      b = a;

      SDL_SetRenderDrawColor(sdlRenderer, 55, 68, 110, 255);
      SDL_RenderClear(sdlRenderer);

      loopGameObjects();

      std::stringstream strs;
      strs << "FPS: " << 1000 / delta;
      TTF_Font *roboto = TTF_OpenFont("../assets/Roboto.ttf", 24);
      SDL_Surface *textSurface = TTF_RenderText_Solid(roboto, (char *) strs.str().c_str(), {0, 255, 0});

      SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdlRenderer, textSurface);
      SDL_Rect r{10, 10, 70, 20};

      SDL_RenderCopy(sdlRenderer, textTexture, nullptr, &r);

      SDL_FreeSurface(textSurface);
      SDL_DestroyTexture(textTexture);

      SDL_RenderPresent(sdlRenderer);

    }

  }

  // Cleanup
  SDL_DestroyWindow(sdlWindow);
  SDL_Quit();

}

void Game::handleWindowEvent(SDL_Event event) {
  switch (event.window.event) {
    case SDL_WINDOWEVENT_CLOSE:
      std::cout << "Exiting game\n";
      quit = true;
      return;
  }
}

// Tnx Aiken
void Game::handleKeyDownEvent(SDL_Event event) {
  keys[event.key.keysym.sym] = true;
}

void Game::handleKeyUpEvent(SDL_Event event) {
  keys[event.key.keysym.sym] = false;
}

void Game::handleMouseMotionEvent(SDL_Event event) {
  mousePosition = Position(event.motion.x, event.motion.y);
}

void Game::registerGameObject(GameObject *gameObject) {
  gameObjects.push_back(gameObject);
  gameObject->game = this;
  auto *cameraComponent = gameObject->getComponentOfType<CameraComponent>();
  if (cameraComponent) {
    camera = gameObject;
    return;
  }
}

void Game::setupGameObjects() {
  for (auto &gameObject: gameObjects)
    gameObject->setup();
}

void Game::loopGameObjects() {
  for (auto &gameObject: gameObjects)
    gameObject->loop();
}

SDL_Renderer *Game::getRenderer() {
  return sdlRenderer;
}

Position Game::getCameraPosition() {
  Position position = camera->position;
  position.x += 200;
  return position;
}

void Game::setCameraPosition(Position position) {
  camera->position = position;
}

bool Game::getKey(int key) {
  return keys[key];
}

std::map<int, bool> Game::getKeys() {
  return keys;
}

std::vector<GameObject *> Game::getGameObjects() {
  return gameObjects;
}

Size Game::getWindowSize() {
  return windowSize;
}

Position Game::getMousePosition() {
  return mousePosition;
}
