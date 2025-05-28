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
static void swapPlayer(qualifiers::Player &a, qualifiers::Player &b) {
  qualifiers::Player t = a;
  a = b;
  b = t;
}
static void shufflePlayers(qualifiers::Player arr[], int n) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  for (int i = n - 1; i > 0; --i) {
    int j = std::rand() % (i + 1);
    swapPlayer(arr[i], arr[j]);
  }
}

// linked-list queue
struct Node {
  qualifiers::Player p;
  Node *next;
  Node(const qualifiers::Player &pl) : p(pl), next(nullptr) {}
};

static void enqueue(Node *&front, Node *&rear, const qualifiers::Player &pl,
                    int &cnt) {
  Node *n = new Node(pl);
  if (!rear)
    front = rear = n;
  else
    rear->next = n, rear = n;
  ++cnt;
}

static qualifiers::Player dequeue(Node *&front, Node *&rear, int &cnt) {
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

bool winnerByOddsBracket(const qualifiers::Player &p1,
                         const qualifiers::Player &p2) {
  int diff = std::abs(p1.tier - p2.tier);
  int shift = std::min(50, 15 * diff);
  int p1Chance = 50 + ((p2.tier > p1.tier) ? shift : -shift);
  static std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(1, 100);
  return dist(rng) <= p1Chance;
}

static int knockoutMatchCounter = 1;

void runKnockoutStage(qualifiers::Player players[], int count) {
  shufflePlayers(players, count);
  std::cout << "\n-- Bracket Entrants: --\n";
  for (int i = 0; i < count; ++i) {
    std::cout << "[" << players[i].id << "] " << players[i].name << " "
              << "[Tier " << players[i].tier << "] \n";
  }
  std::cout << "\n\n";

  Node *front = nullptr, *rear = nullptr;
  int qCount = 0;
  for (int i = 0; i < count; ++i)
    enqueue(front, rear, players[i], qCount);

  std::cout << "-- Single-Elimination --\n";
  while (qCount > 1) {
    qualifiers::Player p1 = dequeue(front, rear, qCount);
    qualifiers::Player p2 = dequeue(front, rear, qCount);

    std::cout << p1.id << " vs " << p2.id << " -> ";
    // use tier‐odds logic instead of direct rank compare
    bool p1Wins = winnerByOddsBracket(p1, p2);
    qualifiers::Player win = p1Wins ? p1 : p2;
    std::cout << "Winner: " << win.id << "\n";

    // **NEW**: log this match
    game_log::MatchResult m;
    m.id = "M" + std::to_string(knockoutMatchCounter++);
    m.p1 = p1.id;
    m.p2 = p2.id;
    m.winner = win.id;
    m.score1 = 0;
    m.score2 = 0;
    m.timestamp = local_time::currentTimestamp();
    game_log::logMatch(m);

    enqueue(front, rear, win, qCount);
  }
  if (qCount == 1) {
    qualifiers::Player champ = dequeue(front, rear, qCount);
    std::cout << "\nChampion: " << "[" << champ.id << "] " << champ.name << " "
              << "[Tier " << champ.tier << "] \n";
  }
}
