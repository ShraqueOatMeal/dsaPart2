#include "qualifiers.h"
#include "group_stage.h"
#include "bracket_stage.h"
#include "game_log.h"
#include <iostream>

int main() {
    // 1) (Optional) Hard-coded test players  
    qualifiers::Player players[] = {
        {"P031", "Marcus Tan",       "20/5/2025 9:23",  false, false, 10, true,  5, 0, "", 1},
        {"P028", "Grace Lim",        "20/5/2025 8:57",  false, false, 11, true,  4, 1, "", 1},
        {"P001", "Alex Yong",        "20/5/2025 9:05",  false, false, 12, true,  2, 0, "", 1},
        {"P026", "Leon Chen",        "20/5/2025 9:16",  false, false, 13, true,  4, 0, "", 1},
        {"P013", "Ong Siew",         "20/5/2025 9:25",  false, false, 14, true,  4, 1, "", 1},
        {"P004", "Jason Leong",      "20/5/2025 9:12",  false, false, 15, true,  3, 2, "", 1},
        {"P016", "Tan Jing",         "20/5/2025 9:02",  false, false, 16, true,  3, 0, "", 1},
        {"P002", "Nabil Tan",        "20/5/2025 9:07",  false, false, 17, true,  0, 2, "", 1},
        {"P020", "Chong Wei",        "20/5/2025 9:18",  false, false, 18, true,  3, 1, "", 2},
        {"P008", "Ahmad Faizal",     "20/5/2025 8:50",  false, false, 19, true,  3, 1, "", 2},
        {"P022", "Ah Chong",         "20/5/2025 8:44",  false, false, 20, true,  0, 3, "", 2},
        {"P006", "Alvin Kwan",       "20/5/2025 9:10",  false, false, 21, true,  1, 2, "", 2},
        {"P011", "Rahul Kumar",      "20/5/2025 9:20",  false, false, 22, true,  2, 2, "", 2},
        {"P017", "Muhammad Hakim",   "20/5/2025 9:08",  false, false, 23, true,  2, 2, "", 2},
        {"P025", "Farah Azlan",      "20/5/2025 8:49",  false, false, 24, true,  3, 2, "", 2},
        {"P007", "Mei Ling",         "20/5/2025 8:47",  false, false, 25, true,  2, 1, "", 2},
        {"P023", "Sanjay Pillai",    "20/5/2025 9:28",  false, false, 26, true,  2, 1, "", 3},
        {"P014", "Nur Aisyah",       "20/5/2025 8:58",  false, false, 27, true,  2, 3, "", 3},
        {"P010", "Lim Wei",          "20/5/2025 9:15",  false, false, 28, true,  0, 3, "", 3},
        {"P019", "Nurul Iman",       "20/5/2025 8:59",  false, false, 29, true,  2, 0, "", 3},
        {"P003", "Cheryl Lim",       "20/5/2025 8:55",  true,  false, 30, true,  1, 1, "", 3},
        {"P012", "Tan Mei",          "20/5/2025 8:40",  true,  false, 31, true,  1, 3, "", 3},
        {"P029", "Brandon Koh",      "20/5/2025 9:27",  false, false, 32, true,  2, 2, "", 3},
        {"P021", "Preeti Rao",       "20/5/2025 9:22",  true,  false, 34, true,  1, 2, "", 4},
        {"P015", "Lee Jun",          "20/5/2025 9:30",  true,  false, 35, false, 0, 1, "", 4},
        {"P032", "Pamela Ong",       "20/5/2025 8:54",  false, false, 36, true,  1, 4, "", 4},
        {"P024", "Jessica Tan",      "20/5/2025 9:32",  true,  false, 37, false, 0, 0, "", 4},
        {"P030", "Amira Hassan",     "20/5/2025 9:13",  true,  false, 38, false, 0, 2, "", 4},
        {"P027", "Shafiq Ismail",    "20/5/2025 9:11",  true,  false, 39, true,  1, 3, "", 4},
        {"P018", "Vikram Singh",     "20/5/2025 9:03",  true,  false, 40, true,  1, 4, "", 4},
        {"P005", "Sarah Chua",       "20/5/2025 9:01",  true,  false, 45, false, 0, 0, "", 4}
    };
    int totalPlayers = sizeof(players) / sizeof(players[0]);

    std::cout << totalPlayers << " players loaded in code.\n";

    // 2) Optionally override with CSV load
    totalPlayers = qualifiers::loadPlayers("tourneydata.csv", players);
    if (totalPlayers < 2) {
        std::cout << "Not enough players.\n";
        return 1;
    }

    // 3) Initialize the log
    game_log log;
    log.initGameLog();

    // 4) Qualifiers
    qualifiers::Player qualified[qualifiers::MAX_PLAYERS];
    int qCount = qualifiers::runQualifiers(players, totalPlayers, qualified);
    std::cout << "\n>>> " << qCount << " advance from Qualifiers.\n";

    // 5) Group Stage
    qualifiers::Player groupAdvance[qualifiers::MAX_PLAYERS];
    int gCount = 0;
    group_stage::runGroupStage(qualified, qCount, groupAdvance, gCount);
    std::cout << "\n>>> " << gCount << " advance from Groups.\n";

    // 6) Single-Elimination
    bracket_stage::runKnockoutStage(groupAdvance, gCount);

    // 7) Print & save history
    // If these are static methods:
    game_log::printRecentMatches();
    game_log::printAllHistory();
    game_log::printAllPlayerStats();

    return 0;
}
