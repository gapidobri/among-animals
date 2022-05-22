#include "engine/GameObject/GameObject.h"
#include "engine/Game/Game.h"
#include "engine/components/TextureComponent/TextureComponent.h"
#include "engine/components/CameraComponent/CameraComponent.h"
#include "engine/components/NavigationComponent/NavigationComponent.h"
#include "engine/components/CollisionComponent/CollisionComponent.h"
#include "engine/components/PhysicsComponent/PhysicsComponent.h"
#include "engine/components/BackgroundComponent/BackgroundComponent.h"
#include "engine/components/EnemyComponent/EnemyComponent.h"
#include "engine/components/AnimalComponent/AnimalComponent.h"
#include "engine/components/PlayerComponent/PlayerComponent.h"
#include "engine/components/MenuComponent/MenuComponent.h"
#include "engine/components/ScoreboardComponent/ScoreboardComponent.h"
#include <iostream>

Game *game = nullptr;

int startMenu();
void startScoreboard();

void startLevel(int enemies, int animals);

void addAnimal(GameObject *player, float offset);

void addEnemy(GameObject *target, float offset);

void addLab(float offset);

int main() {

  std::srand(time(nullptr));

  game = new Game({1280, 720});
  int selected = startMenu();
  int points = 0;
  std::string name;
  std::ofstream scoreboardFile;

  switch (selected) {
    case 0:
      std::cout << "Vpisi svoje ime: ";
      std::getline(std::cin, name);

      game = new Game({1280, 720});
      startLevel(5, 3);
      game->start();
      points += game->getPoints();

      game = new Game({1280, 720});
      startLevel(10, 5);
      game->start();
      points += game->getPoints();

      game = new Game({1280, 720});
      startLevel(15, 8);
      game->start();
      points += game->getPoints();

      scoreboardFile.open("scoreboard.txt", std::ios::app);
      scoreboardFile << name << " " << points << '\n';
      scoreboardFile.close();

      break;

    case 1:

      startScoreboard();
      main();

      break;

    case 2:
      game = new Game({1280, 720});
      startLevel(0, 3);
      game->setReplay(true);
      game->start();
      break;

  }

  return 0;
}

int startMenu() {

  auto *gameObject = new GameObject();

  auto *cameraComponent = new CameraComponent();
  gameObject->registerComponent(cameraComponent);
  auto *menuComponent = new MenuComponent();
  gameObject->registerComponent(menuComponent);

  game->registerGameObject(gameObject);
  game->start();

  return menuComponent->selected;

}

void startScoreboard() {

  game = new Game({1280, 720});
  auto *gameObject = new GameObject();

  auto *cameraComponent = new CameraComponent();
  gameObject->registerComponent(cameraComponent);
  auto *scoreboardComponent = new ScoreboardComponent();
  gameObject->registerComponent(scoreboardComponent);

  game->registerGameObject(gameObject);
  game->start();

}

void startLevel(int enemies, int animals) {

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

  float offset = 300;
  for (int i = 0; i < animals; i++) {

    addLab(offset);
    addAnimal(player, offset + 100);

    float offset2 = 0;
    for (int j = 0; j < enemies; j++) {
      offset2 += (float) (random() % 1000);
      addEnemy(player, offset2 + offset);
    }

    offset += float(random() % 20000);
  }

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
  player->registerComponent(new PlayerComponent(10, animals));
  game->registerGameObject(player);

}

void addAnimal(GameObject *player, float offset) {
  auto *dog = new GameObject(offset, 0);
  dog->setAnchor(Start, End);

  auto *textureComponent = new TextureComponent("animals/1 Dog/Idle.png", 1.5, true, GameObjectState::Idle);
  textureComponent->setFrameCount(4);
  dog->registerComponent(textureComponent);

  dog->registerComponent(new CollisionComponent());

  auto *animalComponent = new AnimalComponent();
  animalComponent->setPlayer(player);
  dog->registerComponent(animalComponent);

  game->registerGameObject(dog);
}

void addLab(float offset) {
  auto *lab = new GameObject(offset, 0);
  lab->setAnchor(Anchor::Start, Anchor::End);
  lab->registerComponent((new TextureComponent("lab.png"))->setScale(2.0));
  game->registerGameObject(lab);
}

void addEnemy(GameObject *target, float offset) {
  auto *enemy = new GameObject(offset, 0);
  enemy->setAnchor(Anchor::Start, Anchor::End);
  enemy->setSize({50, 0});

  enemy->registerComponent(
      (new TextureComponent("enemy/Biker_idle.png", 2, true, GameObjectState::Idle))
          ->setFrameCount(4)
          ->applyCrop(0, 0, 12, 0)
  );
  enemy->registerComponent(
      (new TextureComponent("enemy/Biker_run.png", 2, true, GameObjectState::Moving))
          ->setFrameCount(6)
          ->applyCrop(0, 0, 12, 0)
  );

  enemy->registerComponent(new CollisionComponent());

  auto enemyComponent = new EnemyComponent();
  enemyComponent->setTarget(target);
  enemy->registerComponent(enemyComponent);

  game->registerGameObject(enemy);
}