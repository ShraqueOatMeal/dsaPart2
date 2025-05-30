#pragma once

#include <string>

/// The “qualifiers” class encapsulates player data + helper routines
class qualifiers {
public:
    /// Maximum number of players we can load
    static constexpr int MAX_PLAYERS = 128;

    /// A single player record
    struct Player {
    std::string id;                  // player_id
    std::string name;                // player_name
    std::string registration_time;   // registration_time
    bool        isWildcard;         // is_wildcard == "Yes"
    bool        is_early_bird;       // is_early_bird == "Yes"
    int         rank;             // ranking
    bool        check_in_status;     // check_in_status == "Yes"
    int         total_wins;          // total_wins
    int         total_lost;          // total_lost
    std::string result_in_tourney;   // result_in_touney (win:lose) — here as raw string
    int         tier;         // tier_rating
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
    int static runQualifiers(qualifiers::Player players[],
                  int playerCount,
                  qualifiers::Player out[]);
};

/// Run the bracket of qualifiers:  
///   players[0..playerCount) ⇒ out[0..]  
/// returns how many actually advanced


