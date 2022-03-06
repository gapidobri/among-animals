#include <iostream>
#include "engine/GameObject/GameObject.h"
#include "engine/Game/Game.h"
#include "engine/components/TextureComponent/TextureComponent.h"
#include "engine/components/CameraComponent/CameraComponent.h"
#include "engine/components/NavigationComponent/NavigationComponent.h"
#include "engine/components/CollisionComponent/CollisionComponent.h"
#include "engine/components/PhysicsComponent/PhysicsComponent.h"
#include "engine/components/BackgroundComponent/BackgroundComponent.h"
#include "engine/components/ProjectileComponent/ProjectileComponent.h"
#include "engine/components/EnemyComponent/EnemyComponent.h"

int main() {

  std::srand(time(nullptr));
  std::cout << "Starting game\n";

  auto *game = new Game({1280, 720});

  auto *player = new GameObject(0, -200);

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

  float offset = 0;
  for (int i = 0; i < 10; i++) {
    auto *lab = new GameObject(offset, 0);
    lab->setAnchor(Anchor::Start, Anchor::End);
    lab->registerComponent((new TextureComponent("lab.png"))->setScale(2.0));
    game->registerGameObject(lab);

    float offset2 = 0;
    for (int j = 0; j < 10; j++) {
      offset2 += rand() % 1000;
      auto *enemy = new GameObject(offset2 + offset, 0);
      enemy->setAnchor(Anchor::Start, Anchor::End);
      enemy->registerComponent(
          (new TextureComponent("enemy/Biker_idle.png", 2, true, GameObjectState::Idle))
              ->setFrameCount(4)
      );
      enemy->registerComponent(
          (new TextureComponent("enemy/Biker_run.png", 2, true, GameObjectState::Moving))
              ->setFrameCount(6)
      );
      auto enemyComponent = new EnemyComponent();
      enemyComponent->setTarget(player);
      enemy->registerComponent(enemyComponent);
      game->registerGameObject(enemy);
    }

    offset += float (random() % 20000);
  }

//  auto *dog = new GameObject(100, -200);
//  auto *textureComponent = new TextureComponent("animals/1 Dog/Idle.png", 1.5, true, GameObjectState::Idle, 0, 4);
//  dog->registerComponent(textureComponent);
//  game->registerGameObject(dog);

  player->setSize({50, 0});
  player->registerComponent(
      (new TextureComponent("player/Cyborg_idle.png", 2, true, GameObjectState::Idle))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(4)
  );
  player->registerComponent(
      (new TextureComponent("player/Cyborg_run.png", 2, true, GameObjectState::Moving))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(6)
  );
  player->registerComponent(
      (new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::JumpingStart, 0, 1))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(4)
  );
  player->registerComponent(
      (new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::Jumping, 1, 2))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(4)
  );
  player->registerComponent(
      (new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::FallingStart, 2, 3))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(4)
  );
  player->registerComponent(
      (new TextureComponent("player/Cyborg_jump.png", 2, true, GameObjectState::Falling, 3, 4))
      ->applyCrop(0, 0, 12, 0)
      ->setFrameCount(4)
  );

  player->registerComponent(new NavigationComponent());
  player->registerComponent(new CollisionComponent());
  player->registerComponent(new PhysicsComponent());
  player->registerComponent(new CameraComponent());
//  player->registerComponent(new ProjectileComponent());
  game->registerGameObject(player);

  game->start();

  return 0;
}
