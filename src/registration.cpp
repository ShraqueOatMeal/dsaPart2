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

void registration::copyToRegistration(const qualifiers::Player* src, int count, registration::Player* dest) {
    for (int i = 0; i < count; ++i) {
        dest[i].id = src[i].id;
        dest[i].name = src[i].name;
        dest[i].registration_time = src[i].registration_time;
        dest[i].isWildcard = src[i].isWildcard;
        dest[i].is_early_bird = src[i].is_early_bird;
        dest[i].rank = src[i].rank;
        dest[i].check_in_status = src[i].check_in_status;
        dest[i].total_wins = src[i].total_wins;
        dest[i].total_lost = src[i].total_lost;
        dest[i].result_in_tourney = src[i].result_in_tourney;
        dest[i].tier = src[i].tier;
    }
}
// PlayerQueue implementation
void registration::PlayerQueue::push(const Player& p) {
    if (full()) return;
    data[rear] = p;
    rear = (rear + 1) % MAX_PLAYERS;
    ++size;
}

void registration::PlayerQueue::pop() {
    if (empty()) return;
    front = (front + 1) % MAX_PLAYERS;
    --size;
}

registration::Player& registration::PlayerQueue::frontPlayer() {
    return data[front];
}

// PlayerPriorityQueue implementation
void registration::PlayerPriorityQueue::push(const Player& p) {
    if (full()) return;
    int i = size - 1;
    int pb = (p.is_early_bird ? 2 : 0) + (p.isWildcard ? 1 : 0);
    while (i >= 0) {
        int pa = (data[i].is_early_bird ? 2 : 0) + (data[i].isWildcard ? 1 : 0);
        if (pa >= pb) break;
        data[i + 1] = data[i];
        --i;
    }
    data[i + 1] = p;
    ++size;
}

void registration::PlayerPriorityQueue::pop() {
    if (!empty()) --size;
}

registration::Player& registration::PlayerPriorityQueue::top() {
    return data[size - 1];
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