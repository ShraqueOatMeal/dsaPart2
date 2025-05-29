#include "game_log.h"
#include <iostream>

game_log::game_log() {
  // Constructor implementation
}

game_log::~game_log() {
  // Destructor implementation
}
// —— globals ——
static game_log::MatchResult recent[game_log::RECENT_SIZE];
static int head = 0, rCount = 0;

static game_log::HistoryNode *historyHead = nullptr;
static game_log::HistoryNode *historyTail = nullptr;

static game_log::PlayerStats stats[game_log::MAX_STATS];
static int statsCount = 0;

// find-or-create a PlayerStats entry
static game_log::PlayerStats *findStats(const std::string &pid) {
  for (int i = 0; i < statsCount; ++i)
    if (stats[i].id == pid)
      return &stats[i];
  stats[statsCount].id = pid;
  return &stats[statsCount++];
}

void initGameLog() {
  head = rCount = 0;
  historyHead = historyTail = nullptr;
  statsCount = 0;
}

void logMatch(const game_log::MatchResult &m) {
  // 1) recent buffer (overwrite oldest once full)
  recent[head] = m;
  head = (head + 1) % game_log::RECENT_SIZE;
  if (rCount < game_log::RECENT_SIZE)
    ++rCount;

  // 2) append to full history list
  game_log::HistoryNode *node = new game_log::HistoryNode(m);
  if (!historyHead)
    historyHead = historyTail = node;
  else {
    historyTail->next = node;
    historyTail = node;
  }

  // 3) update per-player stats
  auto *s1 = findStats(m.p1);
  auto *s2 = findStats(m.p2);
  s1->played++;
  s2->played++;
  if (m.winner == m.p1) {
    s1->won++;
    s2->lost++;
  } else {
    s2->won++;
    s1->lost++;
  }
}

void printRecentMatches() {
  std::cout << "\n--- Last " << rCount << " Matches ---\n";
  for (int i = 0; i < rCount; ++i) {
    int idx = (head - 1 - i + game_log::RECENT_SIZE) % game_log::RECENT_SIZE;
    auto &m = recent[idx];
    std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
              << "(" << m.score2 << ") -> " << "Winner: " << m.winner << " @ "
              << m.timestamp << "\n";
  }
}

void printAllHistory() {
  std::cout << "\n=== Full Match History ===\n";
  for (game_log::HistoryNode *cur = historyHead; cur; cur = cur->next) {
    auto &m = cur->data;
    std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
              << "(" << m.score2 << ") -> " << m.winner << " @ " << m.timestamp
              << "\n";
  }
}

void printPlayerHistory(const std::string &pid) {
  std::cout << "\n=== History for " << pid << " ===\n";
  for (game_log::HistoryNode *cur = historyHead; cur; cur = cur->next) {
    auto &m = cur->data;
    if (m.p1 == pid || m.p2 == pid) {
      std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
                << "(" << m.score2 << ") -> " << m.winner << " @ "
                << m.timestamp << "\n";
    }
  }
}

void printAllPlayerStats() {
  std::cout << "\n=== Player Performance Stats ===\n";
  for (int i = 0; i < statsCount; ++i) {
    auto &s = stats[i];
    std::cout << s.id << "  Played:" << s.played << "  Won:" << s.won
              << "  Lost:" << s.lost << "\n";
  }
}
