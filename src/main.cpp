#include "bracket_stage.h"
#include "game_log.h"
#include "group_stage.h"
#include "local_time.h"
#include "qualifiers.h"
#include "registration.hpp"
#include <iostream>
#include <limits>
using namespace std;

registration ::PlayerQueue playerQueue;
registration ::PlayerPriorityQueue playerPriorityQueue;

int main() {
  // Function to sync check-in status for a player ID
  void syncCheckInStatus(
      const string &pid, registration::Player *registeredPlayer,
      int totalRegisteredPlayers, registration::PlayerQueue &playerQueue,
      registration::PlayerPriorityQueue &playerPriorityQueue);

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

  registration::Player registeredPlayer[] = {
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
  int totalRegisteredPlayers =
      sizeof(registeredPlayer) / sizeof(registeredPlayer[0]);

  for (int i = 0; i < totalRegisteredPlayers; ++i) {
    playerQueue.push(registeredPlayer[i]);
    playerPriorityQueue.push(registeredPlayer[i]);
  }

  while (true) {
    cout << "\n=== Registration Menu ===\n";
    cout << "1. Register New Player\n";
    cout << "2. Display Registered Players List\n";
    cout << "3. Withdraw Player\n";
    cout << "4. Check in Player\n";
    cout << "5. Process Check-in Queue Based on Priority\n";
    cout << "6. Copy Checked-in Players to Qualifiers Array\n";
    cout << "0. Exit Registration Menu\n";
    cout << "Enter choice (0-6): ";
    int regChoice;
    if (!(cin >> regChoice)) {
      cout << "Invalid input. Please enter a number.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear
    // the newline character left in the input buffer
    if (regChoice == 0) {
      cout << "Exiting Registration Menu.\n";
      break;
    }
    switch (regChoice) {
    case 1: {
      registration::Player newPlayer;

      // Find the highest existing player number
      int maxIdNum = 0;
      for (int i = 0; i < totalRegisteredPlayers; ++i) {
        if (registeredPlayer[i].id.length() >= 4 &&
            registeredPlayer[i].id[0] == 'P') {
          int num = stoi(registeredPlayer[i].id.substr(1));
          if (num > maxIdNum)
            maxIdNum = num;
        }
      }
      int nextIdNum = maxIdNum + 1;
      string nextId = "P" + string(3 - to_string(nextIdNum).length(), '0') +
                      to_string(nextIdNum);
      cout << "Adding new player with ID: " << nextId << "\n";
      newPlayer.id = nextId;

      cout << "Enter player name: ";
      getline(cin, newPlayer.name);
      newPlayer.registration_time = local_time::currentTimestamp();

      cout << "Is this player a wildcard? (1 for Yes, 0 for No): ";
      int isWildcard;
      cin >> isWildcard;
      newPlayer.isWildcard = (isWildcard == 1) ? true : false;
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Clear the newline character from the input buffer

      cout << "Is this player an early bird? (1 for Yes, 0 for No): ";
      int isEarlyBird;
      cin >> isEarlyBird;
      newPlayer.is_early_bird = (isEarlyBird == 1) ? true : false;
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Clear the newline character from the input buffer

      cout << "Enter player rank (default 0): ";
      int rank;
      if (!(cin >> rank)) {
        cout << "Invalid input. Defaulting rank to 0.\n";
        rank = 0; // Default rank
      }
      cin.ignore(numeric_limits<streamsize>::max(),
                 '\n'); // Clear the newline character from the input buffer
      newPlayer.rank = rank;

      newPlayer.check_in_status = false;
      newPlayer.total_wins = 0;
      newPlayer.total_lost = 0;
      newPlayer.result_in_tourney = "";

      int randomTier = (rand() % 4) + 1; // Random tier between 1 and 4
      newPlayer.tier = randomTier;

      registration::addPlayer(newPlayer, registeredPlayer,
                              totalRegisteredPlayers);
      playerQueue.push(newPlayer);
      playerPriorityQueue.push(newPlayer);

      cout << "New player added \t: " << newPlayer.name << "\n";
      cout << "Player ID \t\t: " << newPlayer.id << "\n";
      cout << "Registration time \t: " << newPlayer.registration_time << "\n";
      cout << "Is Wildcard \t\t: " << (newPlayer.isWildcard ? "Yes" : "No")
           << "\n";
      cout << "Is Early Bird \t\t: " << (newPlayer.is_early_bird ? "Yes" : "No")
           << "\n";
      cout << "Rank \t\t\t: " << newPlayer.rank << "\n";
      cout << "Check-in status \t: "
           << (newPlayer.check_in_status ? "Yes" : "No") << "\n";
      cout << "Tier \t\t\t: " << newPlayer.tier << "\n";
      cout << "Player added successfully!\n";
      continue;
    }

    case 2: {
      cout << "Registered Players List:\n";
      registration::printRegisterList(registeredPlayer, totalRegisteredPlayers);
      continue;
    }

    case 3: {
      cout << "Enter player ID to withdraw (e.g., P031): ";
      string pid;
      getline(cin, pid);
      if (pid.length() < 4 || pid[0] != 'P') {
        cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      } else {
        registration::withdrawPlayer(pid, registeredPlayer,
                                     totalRegisteredPlayers);
        cout << "Player with ID " << pid << " has been withdrawn.\n";
      }
      continue;
    }

    case 4: {

      cout << "Enter player ID to check in (e.g., P031): ";
      string pid;
      getline(cin, pid);
      if (pid.length() < 4 || pid[0] != 'P') {
        cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      } else {
        syncCheckInStatus(pid, registeredPlayer, totalRegisteredPlayers,
                          playerQueue, playerPriorityQueue);
        cout << "Player with ID " << pid << " has been checked in.\n";
      }
      continue;
    }

    case 5: {
      cout << "Checked-in players sorted by priority:\n";
      bool found = false;
      // Print from highest to lowest priority (top is at the end)
      for (int i = playerPriorityQueue.getSize() - 1; i >= 0; --i) {
        const registration::Player &p = playerPriorityQueue.at(i);
        if (p.check_in_status) {
          cout << p.name << " (ID: " << p.id << ")"
               << " - Early Bird: " << (p.is_early_bird ? "Yes" : "No")
               << ", Wildcard: " << (p.isWildcard ? "Yes" : "No") << "\n";
          found = true;
        }
      }
      if (!found) {
        cout << "No players have checked in yet.\n";
      }
      continue;
    }

    case 6: {
      // Separate checked-in players into qualifiers and direct-to-bracket
      qualifiers::Player qualifiers[registration::MAX_PLAYERS];
      int qualifiersCount = 0;
      qualifiers::Player directBracket[registration::MAX_PLAYERS];
      int directBracketCount = 0;

      for (int i = 0; i < totalRegisteredPlayers; ++i) {
        if (registeredPlayer[i].check_in_status) {
          if (registeredPlayer[i].is_early_bird ||
              registeredPlayer[i].isWildcard) {
            // Priority to bracket
            directBracket[directBracketCount++] =
                qualifiers::Player{registeredPlayer[i].id,
                                   registeredPlayer[i].name,
                                   registeredPlayer[i].registration_time,
                                   registeredPlayer[i].isWildcard,
                                   registeredPlayer[i].is_early_bird,
                                   registeredPlayer[i].rank,
                                   registeredPlayer[i].check_in_status,
                                   registeredPlayer[i].total_wins,
                                   registeredPlayer[i].total_lost,
                                   registeredPlayer[i].result_in_tourney,
                                   registeredPlayer[i].tier};
          } else {
            // Qualifiers Player
            qualifiers[qualifiersCount++] =
                qualifiers::Player{registeredPlayer[i].id,
                                   registeredPlayer[i].name,
                                   registeredPlayer[i].registration_time,
                                   registeredPlayer[i].isWildcard,
                                   registeredPlayer[i].is_early_bird,
                                   registeredPlayer[i].rank,
                                   registeredPlayer[i].check_in_status,
                                   registeredPlayer[i].total_wins,
                                   registeredPlayer[i].total_lost,
                                   registeredPlayer[i].result_in_tourney,
                                   registeredPlayer[i].tier};
          }
        }
      }

      cout << qualifiersCount << " players go to qualifiers.\n";
      cout << directBracketCount << " players go straight to bracket stage.\n";

      continue;
    }
    default:
      cout << "Invalid choice. Please select 0-6.\n";
    }
  }

  cout << totalPlayers << " players loaded in code.\n";

  if (totalPlayers < 2) {
    cout << "Not enough players.\n";
    return 1;
  }

  game_log log;
  log.initGameLog();

  // Qualifiers
  // After registration menu, before tournament stages:
  qualifiers::Player qualifiers[registration::MAX_PLAYERS];
  int qualifiersCount = 0;
  qualifiers::Player directBracket[registration::MAX_PLAYERS];
  int directBracketCount = 0;

  // Split checked-in players into qualifiers and direct-to-bracket
  for (int i = 0; i < totalRegisteredPlayers; ++i) {
    if (registeredPlayer[i].check_in_status) {
      if (registeredPlayer[i].is_early_bird || registeredPlayer[i].isWildcard) {
        // Priority: straight to bracket
        directBracket[directBracketCount++] =
            qualifiers::Player{registeredPlayer[i].id,
                               registeredPlayer[i].name,
                               registeredPlayer[i].registration_time,
                               registeredPlayer[i].isWildcard,
                               registeredPlayer[i].is_early_bird,
                               registeredPlayer[i].rank,
                               registeredPlayer[i].check_in_status,
                               registeredPlayer[i].total_wins,
                               registeredPlayer[i].total_lost,
                               registeredPlayer[i].result_in_tourney,
                               registeredPlayer[i].tier};
      } else {
        // Must play qualifiers
        qualifiers[qualifiersCount++] =
            qualifiers::Player{registeredPlayer[i].id,
                               registeredPlayer[i].name,
                               registeredPlayer[i].registration_time,
                               registeredPlayer[i].isWildcard,
                               registeredPlayer[i].is_early_bird,
                               registeredPlayer[i].rank,
                               registeredPlayer[i].check_in_status,
                               registeredPlayer[i].total_wins,
                               registeredPlayer[i].total_lost,
                               registeredPlayer[i].result_in_tourney,
                               registeredPlayer[i].tier};
      }
    }
  }

  cout << qualifiersCount << " players go to qualifiers.\n";
  cout << directBracketCount << " players go straight to bracket stage.\n";

  // Run qualifiers for non-priority players
  qualifiers::Player qualified[registration::MAX_PLAYERS];
  int qCount =
      qualifiers::runQualifiers(qualifiers, qualifiersCount, qualified);
  cout << "\n>>> " << qCount << " advance from Qualifiers.\n";

  // Merge directBracket and qualified for bracket stage
  qualifiers::Player bracketPlayers[registration::MAX_PLAYERS];
  int bracketCount = 0;
  for (int i = 0; i < directBracketCount; ++i)
    bracketPlayers[bracketCount++] = directBracket[i];
  for (int i = 0; i < qCount; ++i)
    bracketPlayers[bracketCount++] = qualified[i];

  // Group Stage
  qualifiers::Player groupAdvance[qualifiers::MAX_PLAYERS];
  int gCount = 0;
  group_stage::runGroupStage(bracketPlayers, bracketCount, groupAdvance,
                             gCount);
  cout << "\n>>> " << gCount << " advance from Groups.\n";

  // Single-Elimination
  bracket_stage::runKnockoutStage(groupAdvance, gCount);

  // Print & save history
  game_log::printRecentMatches();

  // Helper function to sync check-in status for a player ID
  void syncCheckInStatus(
      const string &pid, registration::Player *registeredPlayer,
      int totalRegisteredPlayers, registration::PlayerQueue &playerQueue,
      registration::PlayerPriorityQueue &playerPriorityQueue);

  while (true) {
    cout << "\n=== Tournament Menu ===\n";
    cout << "1. View Recent Matches\n";
    cout << "2. View Full Match History\n";
    cout << "3. View Stage-Specific History\n";
    cout << "4. View Player's Match History\n";
    cout << "5. View All Player Stats\n";
    cout << "6. View Player Stats\n";
    cout << "0. Exit\n";
    cout << "Enter choice (0-6): ";

    int choice;
    if (!(cin >> choice)) {
      cout << "Invalid input. Please enter a number.\n";
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 0) {
      cout << "Exiting program.\n";
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
      cout << "Enter stage prefix (Q for Qualifiers, G for Group Stage, M "
              "for Knockout): ";
      string stagePrefix;
      getline(cin, stagePrefix);
      if (stagePrefix.empty() ||
          (stagePrefix != "Q" && stagePrefix != "G" && stagePrefix != "M")) {
        cout << "Invalid stage prefix. Use Q, G, or M.\n";
      } else {
        game_log::printStageHistory(stagePrefix);
      }
      continue;
    }
    case 4: {
      cout << "Enter player ID" << " (e.g., P031): ";
      string pid;
      getline(cin, pid);
      if (pid.length() < 4 || pid[0] != 'P') {
        cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      } else {
        game_log::printPlayerHistory(pid);
      }
      continue;
    }
    case 5:
      game_log::printAllPlayerStats();
      continue;
    case 6: {
      cout << "Enter player ID" << " (e.g., P031): ";
      string pid;
      getline(cin, pid);
      if (pid.length() < 4 || pid[0] != 'P')
        cout << "Invalid player ID. Use format: PXXX (e.g., P031).\n";
      else
        game_log::printPlayerStats(pid);
      continue;
    }
    default:
      cout << "Invalid choice. Please select 0-6.\n";
    }
    return 0;
  }
}

// Helper function to sync check-in status for a player ID
void syncCheckInStatus(const string &pid,
                       registration::Player *registeredPlayer,
                       int totalRegisteredPlayers,
                       registration::PlayerQueue &playerQueue,
                       registration::PlayerPriorityQueue &playerPriorityQueue) {
  // Update in registeredPlayer[]
  for (int i = 0; i < totalRegisteredPlayers; ++i) {
    if (registeredPlayer[i].id == pid) {
      registeredPlayer[i].check_in_status = true;
      break;
    }
  }
  // Update in playerQueue
  for (int i = 0; i < playerQueue.getSize(); ++i) {
    if (playerQueue.at(i).id == pid) {
      playerQueue.at(i).check_in_status = true;
      break;
    }
  }
  // Update in playerPriorityQueue
  for (int i = 0; i < playerPriorityQueue.getSize(); ++i) {
    if (playerPriorityQueue.at(i).id == pid) {
      playerPriorityQueue.at(i).check_in_status = true;
      break;
    }
  }
}
