#include <iostream>
#include "registration.hpp"
#include "qualifiers.h"
#include "local_time.h"
using namespace std;


registration::registration() {
    // Constructor implementation
}

registration::~registration() {
    // Destructor implementation
}

void registration::sortById(Player players[], int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            // Skipping  the 'P' 
            int id_i = stoi(players[i].id.substr(1));
            int id_j = stoi(players[j].id.substr(1));
            if (id_i > id_j) {
                // Swap players[i] and players[j]
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
}

void registration::addPlayer(Player &player, Player players[], int &count) {
    if (count < MAX_PLAYERS) {
        players[count++] = player;
    } else {
        cerr << "Cannot add player: Maximum limit reached.\n";
    }
}
void registration::withdrawPlayer(const string &id, Player players[], int &count) {
    for (int i = 0; i < count; ++i) {
        if (players[i].id == id) {
            players[i] = players[--count]; // Replace with last player
            return;
        }
    }
    cerr << "Player with ID " << id << " not found.\n";
}
void registration::updatePlayer(const Player &player, Player players[], int count) {
    for (int i = 0; i < count; ++i) {
        if (players[i].id == player.id) {
            players[i] = player;
            return;
        }
    }
    cerr << "Player with ID " << player.id << " not found.\n";
}
void registration::movePlayerToTop(const string &id, Player players[], int count) {
    for (int i = 0; i < count; ++i) {
        if (players[i].id == id) {
            Player temp = players[i];
            for (int j = i; j > 0; --j) {
                players[j] = players[j - 1];
            }
            players[0] = temp;
            return;
        }
    }
    cerr << "Player with ID " << id << " not found.\n";
}

void registration::checkInPlayer(const string &id, Player players[], int count) {
    for (int i = 0; i < count; ++i) {
        if (players[i].id == id) {
            players[i].check_in_status = true;
            return;
        }
    }
    cerr << "Player with ID " << id << " not found.\n";
}

void registration::copyToRegistration(const registration::Player* players, int count, registration::Player* out) {
    for (int i = 0; i < count; ++i) {
        out[i].id = players[i].id;
        out[i].name = players[i].name;
        out[i].registration_time = players[i].registration_time;
        out[i].isWildcard = players[i].isWildcard;
        out[i].is_early_bird = players[i].is_early_bird;
        out[i].rank = players[i].rank;
        out[i].check_in_status = players[i].check_in_status;
        out[i].total_wins = players[i].total_wins;
        out[i].total_lost = players[i].total_lost;
        out[i].result_in_tourney = players[i].result_in_tourney;
        out[i].tier = players[i].tier;
    }
}

void registration::printRegisterList(const registration::Player* players, int count) {
    std::cout << "ID\tName\tRegistration Time\tIs Wildcard\tIs Early Bird\tRank\tCheck-in Status\tTotal Wins\tTotal Lost\tResult in Tourney\tTier\n";
    for (int i = 0; i < count; ++i) {
        std::cout << players[i].id << '\t'
                  << players[i].name << '\t'
                  << players[i].registration_time << '\t'
                  << players[i].isWildcard << '\t'
                  << players[i].is_early_bird << '\t'
                  << players[i].rank << '\t'
                  << players[i].check_in_status << '\t'
                  << players[i].total_wins << '\t'
                  << players[i].total_lost << '\t'
                  << players[i].result_in_tourney << '\t'
                  << players[i].tier << '\n';
    }
}