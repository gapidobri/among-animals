#include <iostream>
#include "engine/GameObject/GameObject.h"
#include "engine/Game/Game.h"
#include "engine/components/TextureComponent/TextureComponent.h"
#include "engine/components/FixedPositionComponent/FixedPositionComponent.h"
#include "engine/components/CameraComponent/CameraComponent.h"
#include "engine/components/NavigationComponent/NavigationComponent.h"
#include "engine/components/CollisionComponent/CollisionComponent.h"

int main() {

  std::cout << "Starting game\n";

  auto *game = new Game();

  auto *camera = new GameObject();
  camera->registerComponent(new CameraComponent());
  game->registerGameObject(camera);

  auto *aiken = new GameObject();
  aiken->registerComponent(new TextureComponent());
  game->registerGameObject(aiken);

  auto *aiken2 = new GameObject(200, 150);
  aiken2->registerComponent(new TextureComponent());
  game->registerGameObject(aiken2);

  auto *player = new GameObject();
  player->registerComponent(new TextureComponent());
  player->registerComponent(new NavigationComponent());
  player->registerComponent(new CollisionComponent());
  player->registerComponent(new FixedPositionComponent(400, 270));
  game->registerGameObject(player);

  game->start();

  return 0;
}
