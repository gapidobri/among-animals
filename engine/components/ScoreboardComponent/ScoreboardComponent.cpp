#include "ScoreboardComponent.h"
#include "../../utils/textutils.h"
#include <fstream>

void ScoreboardComponent::setup() {
  Component::setup();

  std::ifstream scoreboardFile("scoreboard.txt");
  std::string line;
  while (std::getline(scoreboardFile, line))
    scoreboard.push_back(line);
  scoreboardFile.close();

  std::reverse(scoreboard.begin(), scoreboard.end());
}

void ScoreboardComponent::loop() {
  Component::loop();

  if (this->gameObject->getGame()->getKey(SDLK_ESCAPE)) {
    this->gameObject->getGame()->end(false);
  }

  int i = 0;
  for (auto &str: scoreboard) {
    renderText(getRenderer(), {100, (float) (i * 30) + 100}, str, 24, false, {255, 255, 255});
    i++;
    if (i >= 5) break;
  }


}
