#pragma once
#include <string>

class qualifiers {
public:
  qualifiers();
  ~qualifiers();

  static const int MAX_PLAYERS = 128;

  struct Player {
    std::string id;
    std::string name;
    bool isWildcard; // if you want to auto-advance wildcards
    int rank;
    int tier; // 1–4, from your CSV’s last column
  };

  // loadPlayers now knows about id, name, wildcard, rank & tier
  int static loadPlayers(const char *filename, Player players[]);

  // heapify helper you already have
  static void buildHeap(Player heap[], int n);

  // your odds-based qualifier
  int static runQualifiers(Player heap[], int heapSize, Player out[]);

  // bool winnerByOdds(const Player &p1, const Player &p2);
};
