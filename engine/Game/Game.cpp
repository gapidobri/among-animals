#include <iostream>
#include "Game.h"
#include "../GameObject/GameObject.h"
#include "../components/CameraComponent/CameraComponent.h"

void Game::start() {

  // Initialize SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Create Window
  sdlWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, 1000, 650, SDL_WINDOW_OPENGL);

  // Create Renderer
  sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);

  SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
  SDL_RenderClear(sdlRenderer);
  SDL_RenderPresent(sdlRenderer);

  setupGameObjects();

  quit = false;
  SDL_Event event;

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

      }
    }

    SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
    SDL_RenderClear(sdlRenderer);

    loopGameObjects();

    SDL_RenderPresent(sdlRenderer);

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

void Game::registerGameObject(GameObject *gameObject) {
  gameObjects.push_back(gameObject);
  gameObject->game = this;
  auto *cameraComponent = gameObject->getComponentOfType<CameraComponent>();
  if (cameraComponent) {
    camera = gameObject;
    return;
  }
}

void Game::registerCamera(GameObject *gameObject) {
  auto *cameraComponent = gameObject->getComponentOfType<CameraComponent>();
  if (!cameraComponent) {
    std::cout << "This game object doesn't have a camera component";
    return;
  }
  camera = gameObject;
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
  return camera->position;
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