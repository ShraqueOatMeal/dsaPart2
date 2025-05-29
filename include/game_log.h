#pragma once
#include <string>

class game_log {
public:
  game_log();
  ~game_log();

  static const int RECENT_SIZE =
      10; // how many matches to keep in the “recent” ring
  static const int MAX_STATS =
      128; // max distinct players we’ll track stats for

  // A single match’s data
  struct MatchResult {
    std::string id;        // e.g. "M001"
    std::string p1, p2;    // player IDs
    std::string winner;    // winner’s ID
    int score1, score2;    // optional
    std::string timestamp; // e.g. "2025-06-01 14:35"
  };

  // Node for the unbounded history list
  struct HistoryNode {
    MatchResult data;
    HistoryNode *next;
    HistoryNode(const MatchResult &m) : data(m), next(nullptr) {}
  };

  // Per-player cumulative stats
  struct PlayerStats {
    std::string id;
    int played = 0;
    int won = 0;
    int lost = 0;
  };

  // API for logging & reporting
  static void initGameLog();
  static void logMatch(const MatchResult &m);

  // “Quick view” of the last RECENT_SIZE matches
  static void printRecentMatches();

  // Full history traversal
  static void printAllHistory();
  static void printPlayerHistory(const std::string &playerID);

  // Stats dump
  static void printAllPlayerStats();
};
