#pragma once
#include "qualifiers.h"

class bracket_stage {
public:
  bracket_stage();
  ~bracket_stage();

  static void runKnockoutStage(qualifiers::Player players[], int count);
};
