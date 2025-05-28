#pragma once
#include "qualifiers.h"

class group_stage {
public:
  group_stage();
  ~group_stage();

  // before matches
  void printGroupPlayers(const qualifiers::Player groupA[], int sizeA,
                         const qualifiers::Player groupB[], int sizeB);

  // after matches
  void printGroupResults(const qualifiers::Player group[], const int wins[],
                         int size, int numAdvance, const char *groupName);

  // main entry
  void runGroupStage(qualifiers::Player qualifiers[], int qCount,
                     qualifiers::Player advancing[], int &advCount);
};
