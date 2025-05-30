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
  static const int HASH_SIZE = 100;

  // A single match’s data
  struct MatchResult {
    std::string id, p1, p2, winner, timestamp;
    int score1, score2; // optional
  };

  // Node for the unbounded history list
  struct HistoryBSTNode {
    MatchResult data;
    HistoryBSTNode *left, *right;
    HistoryBSTNode(const MatchResult &m)
        : data(m), left(nullptr), right(nullptr) {}
  };

  // Per-player cumulative stats
  struct PlayerStats {
    std::string id;
    int played, won, lost;
  };

  struct StatsNode {
    PlayerStats data;
    StatsNode *next;
    StatsNode(const std::string &pid) : data{pid, 0, 0, 0}, next(nullptr) {}
  };

  static unsigned int hash(const std::string &pid);

  // API for logging & reporting
  static void initGameLog();
  static void logMatch(const MatchResult &m);

  // “Quick view” of the last RECENT_SIZE matches
  static void printRecentMatches();

  // Full history traversal
  static void printAllHistoryBST(HistoryBSTNode *root);
  static void printAllHistory();
  static void printPlayerHistoryBST(HistoryBSTNode *root,
                                    const std::string &pid);
  static void printPlayerHistory(const std::string &playerID);

  static void printStageHistoryBST(HistoryBSTNode *root,
                                   const std::string &stagePrefix);
  static void printStageHistory(const std::string &stagePrefix);

  // Stats dump
  static void printAllPlayerStats();
  static void printPlayerStats(const std::string &pid);

  static void insertBST(HistoryBSTNode *&root, const MatchResult &m);
};
