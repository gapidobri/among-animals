#include <iostream>
#include "engine/GameObject/GameObject.h"
#include "engine/Game/Game.h"
#include "engine/components/TextureComponent/TextureComponent.h"
#include "engine/components/CameraComponent/CameraComponent.h"
#include "engine/components/NavigationComponent/NavigationComponent.h"
#include "engine/components/CollisionComponent/CollisionComponent.h"
#include "engine/components/PhysicsComponent/PhysicsComponent.h"

int main() {

  std::cout << "Starting game\n";

  auto *game = new Game();

  auto *background = new GameObject();
  background->registerComponent(new TextureComponent("background.jpeg"));
  background->setSize(Size{200, 200});
  game->registerGameObject(background);

  auto *aiken = new GameObject(100, 100);
  aiken->registerComponent(new TextureComponent("aiken.png"));
  aiken->registerComponent(new PhysicsComponent());
  game->registerGameObject(aiken);

  auto *player = new GameObject();
  player->registerComponent(new TextureComponent("aiken.png"));
  player->registerComponent(new NavigationComponent());
  player->registerComponent(new CollisionComponent());
  player->registerComponent(new PhysicsComponent());
  player->registerComponent(new CameraComponent());
  game->registerGameObject(player);

  game->start();

  return 0;
}
