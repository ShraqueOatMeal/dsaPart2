#include "bracket_stage.h"
#include "game_log.h"
#include "group_stage.h"
#include "qualifiers.h"
#include <iostream>

// Forward declarations for missing functions
void printRecentMatches();
void printAllHistory();
void printAllPlayerStats();

// Forward declaration for runKnockoutStage
void runKnockoutStage(qualifiers::Player players[], int count);
void runGroupStage(qualifiers::Player qualifiers[], int qCount, qualifiers::Player knockouts[], int& kCount);
//testing

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
  int qCount = runQualifiers(heap, total, qualifiers);
  std::cout << "\n>>> " << qCount << " advance from Qualifiers.\n";

  // 3) Group Stage
  qualifiers::Player knockouts[qualifiers::MAX_PLAYERS];
  int kCount = 0;
  runGroupStage(qualifiers, qCount, knockouts, kCount);
  std::cout << "\n>>> " << kCount << " advance from Groups.\n";

  // 4) Single-Elimination
  runKnockoutStage(knockouts, kCount);

  // 5) printing and saving match history
  game_log::printRecentMatches();
  game_log::printAllHistory();
  game_log::printAllPlayerStats();

  return 0;
}
