#pragma once

#include "qualifiers.h"   // for qualifiers::Player

/// Encapsulates the single-elimination bracket logic & logging
class bracket_stage {
public:
    /// Constructor / Destructor (no special state)
    bracket_stage();
    ~bracket_stage();

    /// Tier-odds match outcome: returns true if p1 wins over p2
    static bool winnerByOddsBracket(const qualifiers::Player &p1, const qualifiers::Player &p2);


    /// prints, logs every match, and announces the champion.
    void static runKnockoutStage(qualifiers::Player players[], int count);

private:

    struct Node {
        qualifiers::Player p;
        Node*              next;
        Node(const qualifiers::Player &pl) : p(pl), next(nullptr) {}
    };

    
    /// Fisher–Yates shuffle helper
    static void shufflePlayers(qualifiers::Player arr[], int n);

    /// Swap two players
    static void swapPlayer(qualifiers::Player &a, qualifiers::Player &b);

    static void enqueue(Node *&front,Node *&rear, const qualifiers::Player &pl,int &cnt);
    static qualifiers::Player dequeue(Node *&front,Node *&rear,int &cnt);
};
