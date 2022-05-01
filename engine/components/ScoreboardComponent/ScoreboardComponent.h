#pragma once

#include <vector>
#include "../../Component/Component.h"

class ScoreboardComponent : public Component {

  std::vector<std::string> scoreboard;

  void setup() override;
  void loop() override;

};

