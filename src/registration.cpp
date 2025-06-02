#include "registration.hpp"
#include <iostream>
using namespace std;

registration::registration() {
  // Constructor implementation
}

registration::~registration() {
  // Destructor implementation
}

void registration::addPlayer(Player &player, Player players[], int &count) {
  if (count < MAX_PLAYERS) {
    players[count++] = player;
  } else {
    cerr << "Cannot add player: Maximum limit reached.\n";
  }
}
void registration::withdrawPlayer(const string &id, Player players[],
                                  int &count) {
  for (int i = 0; i < count; ++i) {
    if (players[i].id == id) {
      players[i] = players[--count]; // Replace with last player
      return;
    }
  }
  cerr << "Player with ID " << id << " not found.\n";
}

void registration::checkInPlayer(const string &id, Player players[],
                                 int count) {
  for (int i = 0; i < count; ++i) {
    if (players[i].id == id) {
      players[i].check_in_status = true;
      return;
    }
  }
  cerr << "Player with ID " << id << " not found.\n";
}

void registration::printRegisterList(const registration::Player *players,
                                     int count) {
  std::cout << "ID\tName\tRegistration Time\tIs Wildcard\tIs Early "
               "Bird\tRank\tCheck-in Status\tTotal Wins\tTotal Lost\tResult in "
               "Tourney\tTier\n";
  for (int i = 0; i < count; ++i) {
    std::cout << players[i].id << '\t' << players[i].name << '\t'
              << players[i].registration_time << '\t' << players[i].isWildcard
              << '\t' << players[i].is_early_bird << '\t' << players[i].rank
              << '\t' << players[i].check_in_status << '\t'
              << players[i].total_wins << '\t' << players[i].total_lost << '\t'
              << players[i].result_in_tourney << '\t' << players[i].tier
              << '\n';
  }
}
