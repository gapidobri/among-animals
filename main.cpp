#include <iostream>
#include "engine/GameObject/GameObject.h"
#include "engine/Game/Game.h"
#include "engine/components/TextureComponent/TextureComponent.h"
#include "engine/components/CameraComponent/CameraComponent.h"
#include "engine/components/NavigationComponent/NavigationComponent.h"
#include "engine/components/CollisionComponent/CollisionComponent.h"
#include "engine/components/PhysicsComponent/PhysicsComponent.h"
#include "engine/components/BackgroundComponent/BackgroundComponent.h"

int main() {

  std::cout << "Starting game\n";

  auto *game = new Game({1280, 720});

  auto *background = new GameObject(0, 400);
  background->registerComponent(new BackgroundComponent("background/1.png", 0.1));
  background->registerComponent(new BackgroundComponent("background/2.png", 0.2));
  background->registerComponent(new BackgroundComponent("background/3.png", 0.3));
  background->registerComponent(new BackgroundComponent("background/4.png", 0.4));
  background->registerComponent(new BackgroundComponent("background/5.png", 0.5));
  game->registerGameObject(background);

  auto *floor = new GameObject();
  floor->registerComponent(new TextureComponent("tile.png", 1, {0, 0, 0, 500}));
  floor->registerComponent(new CollisionComponent());
  game->registerGameObject(floor);

  for (int i = 0; i < 15; i++) {
    auto *platform = new GameObject();
    platform->registerComponent(
        new TextureComponent("IndustrialTile_50.png", 1, {(float) (400.0 * i + 100), (float) (-100.0 * i - 150.0)}, {300, 40}));
    platform->registerComponent(new CollisionComponent());
    game->registerGameObject(platform);
  }

  auto *player = new GameObject({0, -200});
  player->registerComponent(new TextureComponent("player/Cyborg_idle.png", 2, true, GameObjectState::Idle));
  player->registerComponent(new TextureComponent("player/Cyborg_run.png", 2, true, GameObjectState::Moving));
  player->registerComponent(new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::JumpingStart, 0, 1));
  player->registerComponent(new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::Jumping, 1, 2));
  player->registerComponent(new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::FallingStart, 2, 3));
  player->registerComponent(new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::Falling, 3, 4));
  player->registerComponent(new NavigationComponent());
  player->registerComponent(new CollisionComponent());
  player->registerComponent(new PhysicsComponent());
  player->registerComponent(new CameraComponent());
  game->registerGameObject(player);

  game->start();

  return 0;
}
