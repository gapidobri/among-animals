#pragma once

#include "../../Component/Component.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::seconds;

typedef std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<double>> Time;

class PhysicsComponent : public Component {

  double speed = 5, direction = 0;
  Position prevPos;

  void setup() override;
  void loop() override;

  static double calcDirection(double, double);

public:

  ComponentType type() override;

};