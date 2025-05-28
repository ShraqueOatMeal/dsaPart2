#include "game_log.h"
#include <iostream>

game_log::game_log() {
  // Constructor implementation
}

game_log::~game_log() {
  // Destructor implementation
}
// —— globals ——
static MatchResult recent[game_log::RECENT_SIZE];
static int head = 0, rCount = 0;

static HistoryNode *historyHead = nullptr;
static HistoryNode *historyTail = nullptr;

static PlayerStats stats[game_log::MAX_STATS];
static int statsCount = 0;

// find-or-create a PlayerStats entry
static PlayerStats *findStats(const std::string &pid) {
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

void logMatch(const MatchResult &m) {
  // 1) recent buffer (overwrite oldest once full)
  recent[head] = m;
  head = (head + 1) % RECENT_SIZE;
  if (rCount < RECENT_SIZE)
    ++rCount;

  // 2) append to full history list
  HistoryNode *node = new HistoryNode(m);
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
    int idx = (head - 1 - i + RECENT_SIZE) % RECENT_SIZE;
    auto &m = recent[idx];
    std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
              << "(" << m.score2 << ") -> " << "Winner: " << m.winner << " @ "
              << m.timestamp << "\n";
  }
}

void printAllHistory() {
  std::cout << "\n=== Full Match History ===\n";
  for (HistoryNode *cur = historyHead; cur; cur = cur->next) {
    auto &m = cur->data;
    std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
              << "(" << m.score2 << ") -> " << m.winner << " @ " << m.timestamp
              << "\n";
  }
}

void printPlayerHistory(const std::string &pid) {
  std::cout << "\n=== History for " << pid << " ===\n";
  for (HistoryNode *cur = historyHead; cur; cur = cur->next) {
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
