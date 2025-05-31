#pragma once
#include <string>
#include <iostream>
using namespace std;

class registration {
public:
    static constexpr int MAX_PLAYERS = 128;

    struct Player {
        string id;
        string name;
        string registration_time;
        bool isWildcard;
        bool is_early_bird;
        int  rank;
        bool check_in_status;
        int  total_wins;
        int  total_lost;
        string result_in_tourney;
        int  tier;
    };
    
    
    // Simple circular queue for Player
    class PlayerQueue {
        Player data[MAX_PLAYERS];
        int front = 0, rear = 0, size = 0;
    public:
        bool empty() const { return size == 0; }
        bool full() const { return size == MAX_PLAYERS; }
        void push(const Player& p) {
            if (full()) return;
            data[rear] = p;
            rear = (rear + 1) % MAX_PLAYERS;
            ++size;
        }
        void pop() {
            if (empty()) return;
            front = (front + 1) % MAX_PLAYERS;
            --size;
        }
        Player& frontPlayer() { return data[front]; }
        int getSize() const { return size; }
        Player& at(int idx) {
            return data[(front + idx) % MAX_PLAYERS];
        }
    };

    // Simple priority queue for Player
    class PlayerPriorityQueue {
        Player data[MAX_PLAYERS];
        int size = 0;
    public:
        bool empty() const { return size == 0; }
        bool full() const { return size == MAX_PLAYERS; }
        void push(const Player& p) {
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
        void pop() { if (!empty()) --size; }
        Player& top() { return data[size - 1]; }
        int getSize() const { return size; }
        Player& at(int idx) {
            if (idx < 0 || idx >= size) throw out_of_range("Index out of range");
            return data[size - 1 - idx];
        }
    };

    registration();
    ~registration();

    static void sortById(Player players[], int count);
    static void addPlayer(Player &player, Player players[], int &count);
    static void withdrawPlayer(const string &id, Player players[], int &count);
    static void updatePlayer(const Player &player, Player players[], int count);
    static void movePlayerToTop(const string &id, Player players[], int count);
    static void checkInPlayer(const string &id, Player players[], int count);

    // Copy helpers
    static void copyToQualifiers(const Player players[], int count, Player out[]);

    // Print the list of registered players
    static void printRegisterList(const Player players[], int count);
};


