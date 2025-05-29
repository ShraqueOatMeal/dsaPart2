#include "group_stage.h"
#include "game_log.h"
#include "local_time.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

group_stage::group_stage() {
  // Constructor implementation
}

group_stage::~group_stage() {
  // Destructor implementation
}

// Helpers for sorting by wins
void group_stage::swapPlayer(qualifiers::Player &a, qualifiers::Player &b) {
  qualifiers::Player t = a;
  a = b;
  b = t;
}
void group_stage::swapInt(int &a, int &b) {
  int t = a;
  a = b;
  b = t;
}

int group_stage::partitionWins(qualifiers::Player arr[], int wins[], int low, int high) {
  int pivot = wins[(low + high) / 2];
  int i = low, j = high;
  while (i <= j) {
    while (wins[i] > pivot)
      ++i;
    while (wins[j] < pivot)
      --j;
    if (i <= j) {
      swapPlayer(arr[i], arr[j]);
      swapInt(wins[i], wins[j]);
      ++i;
      --j;
    }
  }
  return i;
}

void group_stage::quickSortWins(qualifiers::Player arr[], int wins[], int low, int high) {
  if (low < high) {
    int mid = partitionWins(arr, wins, low, high);
    if (low < mid - 1)
      quickSortWins(arr, wins, low, mid - 1);
    if (mid < high)
      quickSortWins(arr, wins, mid, high);
  }
}

bool group_stage::winnerByOddsGroup(const qualifiers::Player &p1, const qualifiers::Player &p2) {
  int diff = p1.tier - p2.tier;
  if (diff < 0) diff = -diff;
  int shift = std::min(50, 15 * diff);
  int p1Chance = 50 + ((p2.tier > p1.tier) ? shift : -shift);
  static std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(1, 100);
  return dist(rng) <= p1Chance;
}

static int groupMatchCounter = 1;

void group_stage::runGroupStage(qualifiers::Player qualifiers[], int qCount, qualifiers::Player advancing[],
                   int &advCount) {
  // 1) Bucket qualifiers by tier (1–4)
  static qualifiers::Player buckets[5][qualifiers::MAX_PLAYERS];
  int tierCount[5] = {0};
  for (int i = 0; i < qCount; ++i) {
    int t = qualifiers[i].tier; // requires Player::tier
    buckets[t][tierCount[t]++] = qualifiers[i];
  }

  // 2) Evenly distribute each tier into two groups
  qualifiers::Player groupA[qualifiers::MAX_PLAYERS], groupB[qualifiers::MAX_PLAYERS];
  int sizeA = 0, sizeB = 0;
  for (int t = 1; t <= 4; ++t) {
    for (int j = 0; j < tierCount[t]; ++j) {
      if ((j % 2) == 0)
        groupA[sizeA++] = buckets[t][j];
      else
        groupB[sizeB++] = buckets[t][j];
    }
  }
  printGroupPlayers(groupA, sizeA, groupB, sizeB);

  // 3) Prepare win counters
  int winsA[qualifiers::MAX_PLAYERS] = {0}, winsB[qualifiers::MAX_PLAYERS] = {0};

  // 4) Round-robin Group A
  for (int i = 0; i < sizeA; ++i) {
    for (int j = i + 1; j < sizeA; ++j) {
      std::cout << "[Group A] " << groupA[i].id << " vs " << groupA[j].id;

      bool aWins = winnerByOddsGroup(groupA[i], groupA[j]);
      std::string winID = aWins ? groupA[i].id : groupA[j].id;

      // update win counts & print
      if (aWins) {
        ++winsA[i];
      } else {
        ++winsA[j];
      }
      std::cout << " -> " << winID << "\n";

      // now log it
      game_log::MatchResult m;
      m.id = "G" + std::to_string(groupMatchCounter++);
      m.p1 = groupA[i].id;
      m.p2 = groupA[j].id;
      m.winner = winID;
      m.score1 = aWins ? 1 : 0;
      m.score2 = aWins ? 0 : 1;
      m.timestamp = local_time::currentTimestamp();
      game_log::logMatch(m);
    }
  }

  // 5) Round-robin Group B (very similar, but use groupB[] everywhere)
  for (int i = 0; i < sizeB; ++i) {
    for (int j = i + 1; j < sizeB; ++j) {
      std::cout << "[Group B] " << groupB[i].id << " vs " << groupB[j].id;

      bool aWins = group_stage::winnerByOddsGroup(groupB[i], groupB[j]);
      std::string winID = aWins ? groupB[i].id : groupB[j].id;

      if (aWins) {
        ++winsB[i];
      } else {
        ++winsB[j];
      }
      std::cout << " -> " << winID << "\n";

      game_log::MatchResult m;
      m.id = "G" + std::to_string(groupMatchCounter++);
      m.p1 = groupB[i].id; // ← was mistakenly using groupA
      m.p2 = groupB[j].id;
      m.winner = winID;
      m.score1 = aWins ? 1 : 0;
      m.score2 = aWins ? 0 : 1;
      m.timestamp = local_time::currentTimestamp();
      game_log::logMatch(m);
    }
  }

  // 6) Sort each group by descending wins
  group_stage::quickSortWins(groupA, winsA, 0, sizeA - 1);
  group_stage::quickSortWins(groupB, winsB, 0, sizeB - 1);

  // 7) Print out results in Groups Stage
  // show Group A results
  group_stage::printGroupResults(groupA, winsA, sizeA, sizeA / 2, "A");

  // show Group B results
  group_stage::printGroupResults(groupB, winsB, sizeB, sizeB / 2, "B");

  // 8) Advance top half from each group
  advCount = 0;
  for (int i = 0; i < sizeA / 2; ++i) {

    advancing[advCount++] = groupA[i];
  }

  for (int i = 0; i < sizeB / 2; ++i) {

    advancing[advCount++] = groupB[i];
  }
}

void group_stage::printGroupPlayers(const qualifiers::Player groupA[], int sizeA, const qualifiers::Player groupB[],
                       int sizeB) {
  std::cout << "\n=== Group Stage Players ===\n";

  std::cout << "     Group A (" << sizeA << " players)\n";
  for (int i = 0; i < sizeA; ++i) {
    std::cout << "  [" << groupA[i].id << "] " << groupA[i].name << " (Tier "
              << groupA[i].tier << ")\n";
  }

  std::cout << "============================\n";

  std::cout << "     Group B (" << sizeB << " players)\n";
  for (int i = 0; i < sizeB; ++i) {
    std::cout << "  [" << groupB[i].id << "] " << groupB[i].name << " (Tier "
              << groupB[i].tier << ")\n";
  }

  std::cout << "============================\n\n";
}

void group_stage::printGroupResults(const qualifiers::Player group[], const int wins[], int size,
                       int numAdvance, const char *groupName) {
  std::cout << "\n=== Results: Group " << groupName << " ===\n";
  for (int i = 0; i < size; ++i) {
    bool advanced = (i < numAdvance);
    std::cout << "[" << group[i].id << "] " << group[i].name << " [Tier "
              << group[i].tier << "] " << "(wins=" << wins[i] << ") "
              << (advanced ? "(Advanced)" : "(Eliminated)") << "\n";
  }
  std::cout << "============================\n";
}
