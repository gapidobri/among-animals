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

//  auto *background = new GameObject(0, 400);
//  background->registerComponent(new TextureComponent("background.jpeg", true));
//  game->registerGameObject(background);

  for (int i = 0; i < 10; i++) {
    auto *platform = new GameObject(600 * i, -50 * i + 250);
    platform->registerComponent(new TextureComponent("floor.png"));
    platform->registerComponent(new CollisionComponent());
    platform->registerComponent(new PhysicsComponent(false, 0.5));
    game->registerGameObject(platform);
  }

  auto *player = new GameObject();
  player->registerComponent(new TextureComponent("avatar.png"));
  player->registerComponent(new NavigationComponent());
  player->registerComponent(new CollisionComponent());
  player->registerComponent(new PhysicsComponent());
  player->registerComponent(new CameraComponent());
  game->registerGameObject(player);

  game->start();

  return 0;
}
