#pragma once

#include "../../Component/Component.h"
#include <vector>

class MenuComponent : public Component {

  std::vector<std::string> options = {"Play", "Leaderboard", "Replay", "Exit"};
  std::map<int, bool> pressedKeys;

  void setup() override;
  void loop() override;

public:
  ComponentType type() override;

  int selected = 0;

};