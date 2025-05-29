#include "bracket_stage.h"
#include "game_log.h"
#include "group_stage.h"
#include "qualifiers.h"
#include <iostream>


// Forward declarations for missing functions
void printRecentMatches();
void printAllHistory();
void printAllPlayerStats();

int main() {
  // 1) Load
  qualifiers::Player heap[qualifiers::MAX_PLAYERS];
  int total = qualifiers::loadPlayers("tourneydata.csv", heap);
  if (total < 2) {
    std::cout << "Not enough players.\n";
    return 0;
  }
  game_log log;
  log.initGameLog();

  // 2) Qualifiers
  qualifiers::Player qualifiers[qualifiers::MAX_PLAYERS];
  int qCount = qualifiers::runQualifiers(heap, total, qualifiers);
  std::cout << "\n>>> " << qCount << " advance from Qualifiers.\n";

  // 3) Group Stage
  qualifiers::Player knockouts[qualifiers::MAX_PLAYERS];
  int kCount = 0;
  group_stage::runGroupStage(qualifiers, qCount, knockouts, kCount);
  std::cout << "\n>>> " << kCount << " advance from Groups.\n";

  // 4) Single-Elimination
  bracket_stage::runKnockoutStage(knockouts, kCount);

  // 5) printing and saving match history
  printRecentMatches();
  printAllHistory();
  printAllPlayerStats();

  return 0;
}
