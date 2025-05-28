#include "bracket_stage.h"
#include "game_log.h"
#include "group_stage.h"
#include "qualifiers.h"
#include <iostream>

int main() {
  // 1) Load
  Player heap[MAX_PLAYERS];
  int total = loadPlayers("tourneydata.csv", heap);
  if (total < 2) {
    std::cout << "Not enough players.\n";
    return 0;
  }
  initGameLog();

  // 2) Qualifiers
  Player qualifiers[MAX_PLAYERS];
  int qCount = runQualifiers(heap, total, qualifiers);
  std::cout << "\n>>> " << qCount << " advance from Qualifiers.\n";

  // 3) Group Stage
  Player knockouts[MAX_PLAYERS];
  int kCount = 0;
  runGroupStage(qualifiers, qCount, knockouts, kCount);
  std::cout << "\n>>> " << kCount << " advance from Groups.\n";

  // 4) Single-Elimination
  runKnockoutStage(knockouts, kCount);

  // 5) printing and saving match history
  printRecentMatches();
  printAllHistory();
  printAllPlayerStats();

  return 0;
}
