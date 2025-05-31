#include "bracket_stage.h"
#include "game_log.h"
#include "group_stage.h"
#include "qualifiers.h"
#include "registration.hpp"
#include "local_time.h"
#include <iostream>
#include <limits>

registration ::PlayerQueue playerQueue;
registration ::PlayerPriorityQueue playerPriorityQueue;

int main() {
  // 1) (Optional) Hard-coded test players
  qualifiers::Player players[] = {
      {"P031", "Marcus Tan", "20/5/2025 9:23", false, false, 10, true, 5, 0, "",
       1},
      {"P028", "Grace Lim", "20/5/2025 8:57", false, false, 11, true, 4, 1, "",
       1},
      {"P001", "Alex Yong", "20/5/2025 9:05", false, false, 12, true, 2, 0, "",
       1},
      {"P026", "Leon Chen", "20/5/2025 9:16", false, false, 13, true, 4, 0, "",
       1},
      {"P013", "Ong Siew", "20/5/2025 9:25", false, false, 14, true, 4, 1, "",
       1},
      {"P004", "Jason Leong", "20/5/2025 9:12", false, false, 15, true, 3, 2,
       "", 1},
      {"P016", "Tan Jing", "20/5/2025 9:02", false, false, 16, true, 3, 0, "",
       1},
      {"P002", "Nabil Tan", "20/5/2025 9:07", false, false, 17, true, 0, 2, "",
       1},
      {"P020", "Chong Wei", "20/5/2025 9:18", false, false, 18, true, 3, 1, "",
       2},
      {"P008", "Ahmad Faizal", "20/5/2025 8:50", false, false, 19, true, 3, 1,
       "", 2},
      {"P022", "Ah Chong", "20/5/2025 8:44", false, false, 20, true, 0, 3, "",
       2},
      {"P006", "Alvin Kwan", "20/5/2025 9:10", false, false, 21, true, 1, 2, "",
       2},
      {"P011", "Rahul Kumar", "20/5/2025 9:20", false, false, 22, true, 2, 2,
       "", 2},
      {"P017", "Muhammad Hakim", "20/5/2025 9:08", false, false, 23, true, 2, 2,
       "", 2},
      {"P025", "Farah Azlan", "20/5/2025 8:49", false, false, 24, true, 3, 2,
       "", 2},
      {"P007", "Mei Ling", "20/5/2025 8:47", false, false, 25, true, 2, 1, "",
       2},
      {"P023", "Sanjay Pillai", "20/5/2025 9:28", false, false, 26, true, 2, 1,
       "", 3},
      {"P014", "Nur Aisyah", "20/5/2025 8:58", false, false, 27, true, 2, 3, "",
       3},
      {"P010", "Lim Wei", "20/5/2025 9:15", false, false, 28, true, 0, 3, "",
       3},
      {"P019", "Nurul Iman", "20/5/2025 8:59", false, false, 29, true, 2, 0, "",
       3},
      {"P003", "Cheryl Lim", "20/5/2025 8:55", true, false, 30, true, 1, 1, "",
       3},
      {"P012", "Tan Mei", "20/5/2025 8:40", true, false, 31, true, 1, 3, "", 3},
      {"P029", "Brandon Koh", "20/5/2025 9:27", false, false, 32, true, 2, 2,
       "", 3},
      {"P021", "Preeti Rao", "20/5/2025 9:22", true, false, 34, true, 1, 2, "",
       4},
      {"P015", "Lee Jun", "20/5/2025 9:30", true, false, 35, false, 0, 1, "",
       4},
      {"P032", "Pamela Ong", "20/5/2025 8:54", false, false, 36, true, 1, 4, "",
       4},
      {"P024", "Jessica Tan", "20/5/2025 9:32", true, false, 37, false, 0, 0,
       "", 4},
      {"P030", "Amira Hassan", "20/5/2025 9:13", true, false, 38, false, 0, 2,
       "", 4},
      {"P027", "Shafiq Ismail", "20/5/2025 9:11", true, false, 39, true, 1, 3,
       "", 4},
      {"P018", "Vikram Singh", "20/5/2025 9:03", true, false, 40, true, 1, 4,
       "", 4},
      {"P005", "Sarah Chua", "20/5/2025 9:01", true, false, 45, false, 0, 0, "",
       4}};
  int totalPlayers = sizeof(players) / sizeof(players[0]);

  std::cout << totalPlayers << " players loaded in code.\n";

  // 2) Optionally override with CSV load
  // totalPlayers = qualifiers::loadPlayers("tourneydata.csv", players);
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

  while (true) {
    std::cout << "\n=== Tournament Menu ===\n";
    std::cout << "1. View Recent Matches\n";
    std::cout << "2. View Full Match History\n";
    std::cout << "3. View Stage-Specific History\n";
    std::cout << "4. View Player's Match History\n";
    std::cout << "5. View All Player Stats\n";
    std::cout << "6. View Player Stats\n";
    std::cout << "7. Display Player Queue\n";
    std::cout << "8. Display Register list\n";
    std::cout << "9. Add new person \n";
    std::cout << "10. Withdraw person \n";
    std::cout << "11. Check in person \n";
    std::cout << "12. Process check in queue based on the priority \n";
    std::cout << "0. Exit\n";
    std::cout << "Enter choice (0-12): ";

    int choice;
    if (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      continue;
    }
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 0) {
      std::cout << "Exiting program.\n";
      break;
    }

    switch (choice) {
    case 1:
      game_log::printRecentMatches();
      continue;
    case 2:
      game_log::printAllHistory();
      continue;
    case 3: {
      std::cout << "Enter stage prefix (Q for Qualifiers, G for Group Stage, M "
                   "for Knockout): ";
      std::string stagePrefix;
      std::getline(std::cin, stagePrefix);
      if (stagePrefix.empty() ||
          (stagePrefix != "Q" && stagePrefix != "G" && stagePrefix != "M")) {
        std::cout << "Invalid stage prefix. Use Q, G, or M.\n";
      } else {
        game_log::printStageHistory(stagePrefix);
      }
      continue;
    }
    case 4: {
      std::cout << "Enter player ID" << " (e.g., P031): ";
      std::string pid;
      std::getline(std::cin, pid);
      if (pid.length() < 4 || pid[0] != 'P') {
        std::cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      } else {
        game_log::printPlayerHistory(pid);
      }
      continue;
    }
    case 5:
      game_log::printAllPlayerStats();
      continue;
    case 6: {
      std::cout << "Enter player ID" << " (e.g., P031): ";
      std::string pid;
      std::getline(std::cin, pid);
      if (pid.length() < 4 || pid[0] != 'P')
        std::cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      else
        game_log::printPlayerStats(pid);
      continue;
    }
    case 7: {
      registration::Player newPlayer;
      int nextIdNum = totalPlayers + 1;
      std::string nextId = "P" + std::string(3 - std::to_string(nextIdNum).length(), '0') + std::to_string(nextIdNum);
      std::cout << "Adding new player with ID: " << nextId << "\n";
      newPlayer.id = nextId;

      std::cout << "Enter player name: ";
      std::getline(std::cin, newPlayer.name);
      newPlayer.registration_time = local_time::currentTimestamp();

      std::cout << "Is this player a wildcard? (1 for Yes, 0 for No): ";
      int isWildcard;
      std::cin >> isWildcard;
      newPlayer.isWildcard = (isWildcard == 1) ? true : false;

      std::cout << "Is this player an early bird? (1 for Yes, 0 for No): ";
      int isEarlyBird;
      std::cin >> isEarlyBird;
      newPlayer.is_early_bird = (isEarlyBird == 1) ? true : false;
      

      newPlayer.rank = 0; // Default rank
      newPlayer.check_in_status = false;
      newPlayer.total_wins = 0;
      newPlayer.total_lost = 0;
      newPlayer.result_in_tourney = "";
      newPlayer.tier = 1; // Default tier

      playerQueue.push(newPlayer);
      std::cout << "New player added \t: " << newPlayer.name << "\n";
      std::cout << "Player ID \t\t: " << newPlayer.id << "\n";
      totalPlayers++;
      
      continue;
    }

    case 8: {
      // Print the registered player list using the player array and count
      registration::Player players[registration::MAX_PLAYERS];
      int count = playerQueue.getSize();
      for (int i = 0; i < count; ++i) {
          players[i] = playerQueue.at(i);
      }
      registration::printRegisterList(players, count);
      continue;
    }


    default:
      std::cout << "Invalid choice. Please select 1-7.\n";
    }
    return 0;
  }
}
