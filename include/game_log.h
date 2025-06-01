#pragma once
#include <string>

class game_log {
public:
  game_log();
  ~game_log();

  static const int RECENT_SIZE = 10; // Matches to keep in the “recent”
  static const int MAX_STATS = 128;  // max distinct players
  static const int HASH_SIZE = 100;

  struct MatchResult {
    std::string id, p1, p2, winner, timestamp;
    int score1, score2;
  };

  // Node for the history list
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

  static void initGameLog();
  static void logMatch(const MatchResult &m);

  static void printRecentMatches();

  static void printAllHistoryBST(HistoryBSTNode *root);
  static void printAllHistory();
  static void printPlayerHistoryBST(HistoryBSTNode *root,
                                    const std::string &pid);
  static void printPlayerHistory(const std::string &playerID);

  static void printStageHistoryBST(HistoryBSTNode *root,
                                   const std::string &stagePrefix);
  static void printStageHistory(const std::string &stagePrefix);

  static void printAllPlayerStats();
  static void printPlayerStats(const std::string &pid);

  static void insertBST(HistoryBSTNode *&root, const MatchResult &m);
};
