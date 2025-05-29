#pragma once

#include <string>

/// The “qualifiers” class encapsulates player data + helper routines
class qualifiers {
public:
    /// Maximum number of players we can load
    static constexpr int MAX_PLAYERS = 128;

    /// A single player record
    struct Player {
        std::string id;
        std::string name;
        bool        isWildcard;
        int         rank;
        int         tier;
    };

    /// C-tor / D-tor (you can leave these empty or omit if you only ever use statics)
    qualifiers();
    ~qualifiers();

    /// Utility routines
    static void        swapPlayer(Player &a, Player &b);
    static void        sortByRank(Player arr[], int n);
    static bool        winnerByOdds(const Player &p1, const Player &p2);

    /// File I/O
    static int         loadPlayers(const char *filename, Player players[]);
};

/// Run the bracket of qualifiers:  
///   players[0..playerCount) ⇒ out[0..]  
/// returns how many actually advanced
int runQualifiers(qualifiers::Player players[],
                  int playerCount,
                  qualifiers::Player out[]);

