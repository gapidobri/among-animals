#include "MenuComponent.h"
#include "../../utils/textutils.h"

void MenuComponent::setup() {
  Component::setup();
}

void MenuComponent::loop() {
  Component::loop();

  std::map<int, bool> keys = gameObject->getGame()->getKeys();

  if (keys[SDLK_UP]) {
    if (!pressedKeys[SDLK_UP] && selected > 0)
      selected--;
    pressedKeys[SDLK_UP] = true;
  } else {
    pressedKeys[SDLK_UP] = false;
  }

  if (keys[SDLK_DOWN]) {
    if (!pressedKeys[SDLK_DOWN] && selected < options.size() - 1)
      selected++;
    pressedKeys[SDLK_DOWN] = true;
  } else {
    pressedKeys[SDLK_DOWN] = false;
  }

  if (keys[13]) {
    gameObject->getGame()->end(false);
  }

  int i = 0;
  for (auto &option: options) {
    renderText(getRenderer(), {50, static_cast<float>(50 * i) + 500}, option, 32, false,
               {255, 255, 255, static_cast<Uint8>(i == selected ? 255 : 100)});
    i++;
  }

}

ComponentType MenuComponent::type() {
  return ComponentType::MenuComponent;
}
