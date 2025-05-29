#pragma once

#include "qualifiers.h"   // for qualifiers::Player

/// Encapsulates the round‐robin group stage logic & printing
class group_stage {
public:
    group_stage();
    ~group_stage();

    /// Tier‐odds winner logic (50% ± shift based on tier difference)
    static bool winnerByOddsGroup(const qualifiers::Player &p1,
                                  const qualifiers::Player &p2);

    /// Run the full group stage:
    void static runGroupStage(qualifiers::Player qualifiers[],
                       int qCount,
                       qualifiers::Player advancing[],
                       int &advCount);

    /// Print the list of players in Group A and Group B
    void static printGroupPlayers(const qualifiers::Player groupA[],
                           int sizeA,
                           const qualifiers::Player groupB[],
                           int sizeB);

    /// Print the final standings, marking the top `numAdvance` as advanced
    void static printGroupResults(const qualifiers::Player group[],
                           const int wins[],
                           int size,
                           int numAdvance,
                           const char *groupName);

private:
    // low-level helpers for sorting by wins
    static void swapPlayer(qualifiers::Player &a, qualifiers::Player &b);
    static void swapInt(int &a, int &b);
    static int  partitionWins(qualifiers::Player arr[],
                              int wins[],
                              int low,
                              int high);
    static void quickSortWins(qualifiers::Player arr[],
                              int wins[],
                              int low,
                              int high);
};
