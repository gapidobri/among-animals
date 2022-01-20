#include "TileComponent.h"

void TileComponent::setup() {
  Component::setup();
}

void TileComponent::loop() {
  Component::loop();


}

ComponentType TileComponent::type() {
  return ComponentType::TileComponent;
}
