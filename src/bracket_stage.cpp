#include "bracket_stage.h"
#include "game_log.h"
#include "local_time.h"
#include "qualifiers.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

bracket_stage::bracket_stage() {
  // Constructor implementation
}

bracket_stage::~bracket_stage() {
  // Destructor implementation
}
//
// shuffle
void bracket_stage::swapPlayer(qualifiers::Player &a, qualifiers::Player &b) {
  qualifiers::Player t = a;
  a = b;
  b = t;
}

void bracket_stage::shufflePlayers(qualifiers::Player arr[], int n) {
  static std::mt19937 rng{std::random_device{}()};
  std::shuffle(arr, arr + n, rng);
}

// linked-list queue
struct Node {
  qualifiers::Player p;
  Node *next;
  Node(const qualifiers::Player &pl) : p(pl), next(nullptr) {}
};

void bracket_stage::enqueue(Node *&front, Node *&rear,
                            const qualifiers::Player &pl, int &cnt) {
  Node *n = new Node(pl);
  if (!rear)
    front = rear = n;
  else
    rear->next = n, rear = n;
  ++cnt;
}

qualifiers::Player bracket_stage::dequeue(Node *&front, Node *&rear, int &cnt) {
  if (!front) {
    std::cerr << "Queue underflow\n";
    return qualifiers::Player{"", "", 0};
  }
  Node *tmp = front;
  qualifiers::Player pl = tmp->p;
  front = front->next;
  if (!front)
    rear = nullptr;
  delete tmp;
  --cnt;
  return pl;
}

bool bracket_stage::winnerByOddsBracket(const qualifiers::Player &p1,
                                        const qualifiers::Player &p2) {
  int diff = p1.tier - p2.tier;
  if (diff < 0)
    diff = -diff;
  int shift = std::min(50, 15 * diff);
  int p1Chance = 50 + ((p2.tier > p1.tier) ? shift : -shift);
  static std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(1, 100);
  return dist(rng) <= p1Chance;
}

static int knockoutMatchCounter = 1;

void bracket_stage::runKnockoutStage(qualifiers::Player players[], int count) {
  bracket_stage::shufflePlayers(players, count);
  std::cout << "\n-- Bracket Entrants: --\n";
  for (int i = 0; i < count; ++i) {
    std::cout << "[" << players[i].id << "] " << players[i].name << " "
              << "[Tier " << players[i].tier << "] \n";
  }
  std::cout << "\n\n";

  Node *front = nullptr, *rear = nullptr;
  int qCount = 0;
  for (int i = 0; i < count; ++i)
    bracket_stage::enqueue(front, rear, players[i], qCount);

  std::cout << "-- Single-Elimination --\n";
  while (qCount > 1) {
    qualifiers::Player p1 = bracket_stage::dequeue(front, rear, qCount);
    qualifiers::Player p2 = bracket_stage::dequeue(front, rear, qCount);

    std::cout << p1.id << " vs " << p2.id << " -> ";
    // use tier‐odds logic instead of direct rank compare
    bool p1Wins = bracket_stage::winnerByOddsBracket(p1, p2);
    qualifiers::Player win = p1Wins ? p1 : p2;
    std::cout << "Winner: " << win.id << "\n";

    int score1 = p1Wins ? 1 : 0;
    int score2 = p1Wins ? 0 : 1;

    // **NEW**: log this match
    game_log::MatchResult m;
    m.id = "M" + std::to_string(knockoutMatchCounter++);
    m.p1 = p1.id;
    m.p2 = p2.id;
    m.winner = win.id;
    m.score1 = score1;
    m.score2 = score2;
    m.timestamp = local_time::currentTimestamp();
    game_log::logMatch(m);

    bracket_stage::enqueue(front, rear, win, qCount);
  }
  if (qCount == 1) {
    qualifiers::Player champ = bracket_stage::dequeue(front, rear, qCount);
    std::cout << "\nChampion: " << "[" << champ.id << "] " << champ.name << " "
              << "[Tier " << champ.tier << "] \n";
  }
}
