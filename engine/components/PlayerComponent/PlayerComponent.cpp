#include "PlayerComponent.h"
#include "../../utils/textutils.h"

PlayerComponent::PlayerComponent() = default;

PlayerComponent::PlayerComponent(int health, int animalCount) {
  this->health = health;
  this->animalCount = animalCount;
}

void PlayerComponent::setup() {
  Component::setup();
}

void PlayerComponent::loop() {
  Component::loop();

  if (health == 0) {
    auto center = gameObject->getGame()->getWindowSize() / 2;
    renderText(getRenderer(), {center.width, 50}, "Konec igre!", 36, true);
    gameObject->getGame()->pause();
  }

  if (animalsCollected == animalCount) {
    gameObject->getGame()->end(false);
  }

  if (godMode > 0) {
    godMode--;
    if (blinkTime == 0) {
      bool hidden = gameObject->getHidden();
      gameObject->setHidden(!hidden);
      blinkTime = 10;
    }
    blinkTime--;
  } else {
    gameObject->setHidden(false);
  }

  renderAnimalsCollected();
  renderHealth();
  renderPoints();
}

void PlayerComponent::damage() {
  if (godMode == 0) {
    health--;
    godMode = 300;
    gameObject->getGame()->addPoints(-10);
  }
}

ComponentType PlayerComponent::type() {
  return ComponentType::PlayerComponent;
}

void PlayerComponent::animalCollected() {
  animalsCollected++;
  gameObject->getGame()->addPoints(50);
}

void PlayerComponent::renderAnimalsCollected() {
  std::stringstream stringStream;
  stringStream << "Resene zivali: " << animalsCollected << '/' << animalCount;
  renderText(getRenderer(), {10, 50}, stringStream.str(), 24);
}

void PlayerComponent::renderHealth() {
  std::stringstream stringStream;
  stringStream << "Zivljenja: " << health;
  renderText(getRenderer(), {10, 80}, stringStream.str(), 24);
}

void PlayerComponent::renderPoints() {
  std::stringstream stringStream;
  stringStream << "Tocke: " << gameObject->getGame()->getPoints();
  renderText(getRenderer(), {10, 110}, stringStream.str(), 24);
}
