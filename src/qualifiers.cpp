#include "qualifiers.h"
#include "game_log.h"
#include "local_time.h"
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string> // ← for std::string
#include <algorithm> // for std::sort


qualifiers::qualifiers() {
  // Constructor implementation
}

qualifiers::~qualifiers() {
  // Destructor implementation
}

// Swap helper
void qualifiers::swapPlayer(qualifiers::Player &a, qualifiers::Player &b) {
  qualifiers::Player tmp = a;
  a = b;
  b = tmp;
}

// Heapify subtree rooted at i (0-indexed) for size n
// static void heapify(qualifiers::Player heap[], int n, int i) {
//   int largest = i;
//   int l = 2 * i + 1;
//   int r = 2 * i + 2;
//   if (l < n && heap[l].rank > heap[largest].rank)
//     largest = l;
//   if (r < n && heap[r].rank > heap[largest].rank)
//     largest = r;
//   if (largest != i) {
//     swapPlayer(heap[i], heap[largest]);
//     heapify(heap, n, largest);
//   }
// }

// void buildHeap(qualifiers::Player heap[], int n) {
//   for (int i = n / 2 - 1; i >= 0; --i) {
//     heapify(heap, n, i);
//   }
// }

// Extract top of heap, shrink n
// static qualifiers::Player extractMax(qualifiers::Player heap[], int &n) {
//   qualifiers::Player top = heap[0];
//   heap[0] = heap[n - 1];
//   --n;
//   heapify(heap, n, 0);
//   return top;
// }

void qualifiers::sortByRank(qualifiers::Player arr[], int n) {
    std::sort(arr, arr + n, [](const qualifiers::Player &a, const qualifiers::Player &b){
        return a.rank > b.rank;
    });
}

int qualifiers::loadPlayers(const char *filename, qualifiers::Player players[]) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening " << filename << "\n";
    return 0;
  }

  std::string line, token;
  int count = 0;

  // skip header
  std::getline(file, line);

  while (std::getline(file, line) && count < qualifiers::MAX_PLAYERS) {
    std::istringstream ss(line);

    // 1) ID
    std::getline(ss, players[count].id, ',');

    // 2) Name
    std::getline(ss, players[count].name, ',');

    // 3) registration_time (skip)
    std::getline(ss, token, ',');

    // 4) is_wildcard
    std::getline(ss, token, ',');
    players[count].isWildcard = (token == "Yes");

    // 5) ranking
    std::getline(ss, token, ',');
    players[count].rank = std::stoi(token);

    // 6) check_in_status, total_wins, total_lost, result_in_tourney (skip 4
    // cols)
    for (int i = 0; i < 4; ++i)
      std::getline(ss, token, ',');

    // 7) tier_rating
    std::getline(ss, token, ',');
    players[count].tier = std::stoi(token);

    ++count;
  }

  return count;
}

// Returns true if p1 wins
bool qualifiers::winnerByOdds(const qualifiers::Player &p1,
                         const qualifiers::Player &p2) {
  int diff = p1.tier - p2.tier;
  if (diff < 0)
    diff = -diff;
  int shift = std::min(50, 15 * diff);

  // better tier = lower number
  int p1Chance = 50 + ((p2.tier > p1.tier) ? shift : -shift);

  static std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> dist(1, 100);
  return dist(rng) <= p1Chance;
}

static int qualifierMatchCounter = 1;

int runQualifiers(qualifiers::Player players[], int playerCount, qualifiers::Player out[]) {
    // 1) Sort all players by rank
    qualifiers::sortByRank(players, playerCount);

    // 2) Bucket into tiers
    static qualifiers::Player buckets[5][qualifiers::MAX_PLAYERS];
    int bucketSize[5] = {0};

    for (int i = 0; i < playerCount; ++i) {
        int t = players[i].tier;
        if (t >= 1 && t <= 4) {
            buckets[t][ bucketSize[t]++ ] = players[i];
        }
    }

    int qCount = 0;
    int matchCounter = 1;

    // 3) Pair them off and decide winners
    for (int t = 1; t <= 4; ++t) {
        int idx = bucketSize[t] - 1;
        while (idx > 0) {
            qualifiers::Player a = buckets[t][idx--];
            qualifiers::Player b = buckets[t][idx--];

            qualifiers::Player winner = qualifiers::winnerByOdds(a, b) ? a : b;
            out[qCount++] = winner;

            std::cout << "[Tier " << t << "] "
                      << a.id << " vs " << b.id
                      << " -> Winner: " << winner.id << "\n";

            // Log it
            game_log::MatchResult m{ "Q" + std::to_string(matchCounter++),
                           a.id, b.id, winner.id, 0, 0,
                           local_time::currentTimestamp() 
                           };
            game_log::logMatch(m);
        }

        // advances if odd count
        if (idx == 0) {
            out[qCount++] = buckets[t][0];
            std::cout << "[Tier " << t << "] "
                      << buckets[t][0].id
                      << " advances by default\n";
        }
    }

    return qCount;
}

// static int qualifierMatchCounter = 1;

// int runQualifiers(qualifiers::Player heap[], int heapSize,
//                   qualifiers::Player out[]) {
//   buildHeap(heap, heapSize);

//   // Extract players into temp[] in descending rank order
//   qualifiers::Player temp[qualifiers::MAX_PLAYERS];
//   int n = heapSize;
//   for (int i = heapSize - 1; i >= 0; --i)
//     temp[i] = extractMax(heap, n);

//   // 1. Group into 4 tiers using 2D array
//   qualifiers::Player buckets[5][qualifiers::MAX_PLAYERS]; // tiers 1-4, ignore index 0
//   int bucketSize[5] = {0};                    // count per tier

//   for (int i = 0; i < heapSize; ++i) {
//     int t = temp[i].tier;
//     if (t >= 1 && t <= 4) {
//       buckets[t][bucketSize[t]++] = temp[i];
//     }
//   }

//   int qCount = 0;
//   int matchCounter = 1;

//   // 2. Iterate each tier and simulate matches
//   for (int t = 1; t <= 4; ++t) {
//     int i = bucketSize[t] - 1;

//     while (i > 0) {
//       qualifiers::Player a = buckets[t][i--];
//       qualifiers::Player b = buckets[t][i--];

//       bool aWins = winnerByOdds(a, b);
//       qualifiers::Player winner = aWins ? a : b;
//       out[qCount++] = winner;

//       std::cout << "[Tier " << t << "] " << a.id << " vs " << b.id
//                 << " -> Winner: " << winner.id << "\n";

//       game_log::MatchResult m;
//       m.id = "Q" + std::to_string(matchCounter++);
//       m.p1 = a.id;
//       m.p2 = b.id;
//       m.winner = winner.id;
//       m.score1 = 0;
//       m.score2 = 0;
//       m.timestamp = local_time::currentTimestamp();
//       game_log::logMatch(m);
//     }

//     // Handle odd player
//     if (i == 0) {
//       out[qCount++] = buckets[t][0];
//       std::cout << "[Tier " << t << "] " << buckets[t][0].id
//                 << " no matchers found eliminated\n";
//     }
//   }

//   return qCount;
// }
