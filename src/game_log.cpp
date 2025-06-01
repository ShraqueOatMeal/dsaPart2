#include "game_log.h"
#include <iostream>

game_log::game_log() {
  // Constructor implementation
}

// —— globals ——
static game_log::MatchResult recent[game_log::RECENT_SIZE];
static int head = 0, rCount = 0;

static game_log::HistoryBSTNode *historyRoot = nullptr;

static game_log::StatsNode *hashTable[game_log::HASH_SIZE];
static int statsCount = 0;

unsigned int game_log::hash(const std::string &pid) {
  unsigned int hash = 0;
  for (char c : pid)
    hash = c + 31 * hash;
  return hash % game_log::HASH_SIZE;
}

// find-or-create a PlayerStats entry
static game_log::PlayerStats *findStats(const std::string &pid) {
  unsigned int hash = game_log::hash(pid);
  game_log::StatsNode *cur = hashTable[hash];
  while (cur) {
    if (cur->data.id == pid)
      return &cur->data;
    cur = cur->next;
  }
  if (statsCount == game_log::MAX_STATS)
    return nullptr;
  game_log::StatsNode *newNode = new game_log::StatsNode(pid);
  newNode->next = hashTable[hash];
  hashTable[hash] = newNode;
  statsCount++;
  return &newNode->data;
}

void game_log::insertBST(game_log::HistoryBSTNode *&root,
                         const game_log::MatchResult &m) {
  if (!root) {
    root = new game_log::HistoryBSTNode(m);
    return;
  }

  int m_num, root_num;

  try {
    m_num = stoi(m.id.substr(1));
    root_num = stoi(root->data.id.substr(1));
  } catch (...) {
    if (m.id < root->data.id)
      insertBST(root->left, m);
    else
      insertBST(root->right, m);
    return;
  }

  if (m_num < root_num)
    insertBST(root->left, m);
  else
    insertBST(root->right, m);
}

void game_log::initGameLog() {
  head = rCount = 0;
  historyRoot = nullptr;
  for (int i = 0; i < game_log::HASH_SIZE; ++i)
    hashTable[i] = nullptr;
  statsCount = 0;
}

void game_log::logMatch(const game_log::MatchResult &m) {
  // Recent buffer (overwrite oldest when full)
  recent[head] = m;
  head = (head + 1) % game_log::RECENT_SIZE;
  if (rCount < game_log::RECENT_SIZE)
    ++rCount;

  insertBST(historyRoot, m);

  // update player stats
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

void game_log::printRecentMatches() {
  std::cout << "\n--- Last " << rCount << " Matches ---\n";
  for (int i = 0; i < rCount; ++i) {
    int idx = (head - 1 - i + game_log::RECENT_SIZE) % game_log::RECENT_SIZE;
    auto &m = recent[idx];
    std::cout << m.id << ": " << m.p1 << "(" << m.score1 << ") vs " << m.p2
              << "(" << m.score2 << ") -> " << "Winner: " << m.winner << " @ "
              << m.timestamp << "\n";
  }
}

void game_log::printAllHistoryBST(HistoryBSTNode *root) {
  if (!root)
    return;
  printAllHistoryBST(root->left);
  std::cout << root->data.id << ": " << root->data.p1 << "("
            << root->data.score1 << ") vs " << root->data.p2 << "("
            << root->data.score2 << ") -> " << root->data.winner << " @ "
            << root->data.timestamp << "\n";
  printAllHistoryBST(root->right);
}

void game_log::printAllHistory() {
  std::cout << "\n=== Full Match History ===\n";
  game_log::printAllHistoryBST(historyRoot);
}

void game_log::printPlayerHistoryBST(game_log::HistoryBSTNode *root,
                                     const std::string &pid) {
  if (!root) {
    return;
  }
  printPlayerHistoryBST(root->left, pid);
  if (root->data.p1 == pid || root->data.p2 == pid) {
    std::cout << root->data.id << ": " << root->data.p1 << " vs "
              << root->data.p2 << " -> " << root->data.winner << " @ "
              << root->data.timestamp << "\n";
  }
  printPlayerHistoryBST(root->right, pid);
}

void game_log::printStageHistoryBST(game_log::HistoryBSTNode *root,
                                    const std::string &stagePrefix) {
  if (!root)
    return;
  game_log::printStageHistoryBST(root->left, stagePrefix);
  auto &m = root->data;
  if (m.id.find(stagePrefix) == 0) { // Check if id starts with stagePrefix
    std::cout << m.id << ": " << m.p1 << " vs " << m.p2 << " -> "
              << "Winner: " << m.winner << " @ " << m.timestamp << "\n";
  }
  game_log::printStageHistoryBST(root->right, stagePrefix);
}

void game_log::printStageHistory(const std::string &stagePrefix) {
  std::cout << "\n=== Matches for stage " << stagePrefix << " ===\n";
  game_log::printStageHistoryBST(historyRoot, stagePrefix);
}

void game_log::printPlayerHistory(const std::string &pid) {
  std::cout << "\n=== History for " << pid << " ===\n";
  printPlayerHistoryBST(historyRoot, pid);
}

void game_log::printAllPlayerStats() {
  std::cout << "\n=== Player Performance Stats ===\n";
  int count[game_log::HASH_SIZE + 1] = {0};

  for (int i = 0; i < game_log::HASH_SIZE; ++i) {
    StatsNode *cur = hashTable[i];
    while (cur) {
      const std::string &pid = cur->data.id;
      if (cur->data.played > 0) {
        try {
          int num = stoi(pid.substr(1));
          if (num >= 1 && num <= game_log::HASH_SIZE) {
            count[num]++;
          }
        } catch (...) {
        }
      }
      cur = cur->next;
    }
  }
  for (int i = 1; i <= game_log::HASH_SIZE; ++i) {
    if (count[i] > 0) {
      char pid[5];
      sprintf(pid, "P%03d", i);
      PlayerStats *s = findStats(pid);
      if (s) {
        std::cout << pid << "  Played:" << s->played << "  Won:" << s->won
                  << "  Lost:" << s->lost << "\n";
      }
    }
  }
}

void game_log::printPlayerStats(const std::string &pid) {
  std::cout << "\n=== Stats for " << pid << " ===\n";
  PlayerStats *s = findStats(pid);
  if (!s || s->played == 0) {
    std::cout << "No stats found.\n";
    return;
  }
  std::cout << "Played:" << s->played << "  Won:" << s->won
            << "  Lost:" << s->lost << "\n";
}

game_log::~game_log() {
  // Destructor implementation
  // Free BST
  HistoryBSTNode *stack[1000]; // Large enough for 71 matches
  int top = -1;
  if (historyRoot)
    stack[++top] = historyRoot;
  while (top >= 0) {
    HistoryBSTNode *node = stack[top--];
    if (node->left)
      stack[++top] = node->left;
    if (node->right)
      stack[++top] = node->right;
    delete node;
  }
  historyRoot = nullptr;

  // Free hash table
  for (int i = 0; i < HASH_SIZE; ++i) {
    StatsNode *cur = hashTable[i];
    while (cur) {
      StatsNode *next = cur->next;
      delete cur;
      cur = next;
    }
    hashTable[i] = nullptr;
  }
}
