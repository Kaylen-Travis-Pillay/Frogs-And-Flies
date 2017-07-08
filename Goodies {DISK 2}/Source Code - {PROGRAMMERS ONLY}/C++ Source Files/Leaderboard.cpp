#include "Leaderboard.h"
#include <algorithm>

Leaderboard::Leaderboard(ktp::DataBaseTable * points, Player * player)
{
	player_points = points;
	game_player = player;
}

void Leaderboard::run_Leaderboards()
{
	// Updating the local players points
	if (!game_player->isPlayerGuest()) {
		
		ktp::DetailsContainer_VEC points_temp_VEC;
		for (int points = 0; points < 5; points++) {
			points_temp_VEC.push_back(std::to_string(game_player->GetPlayerPoints()[points]));
		}
		points_temp_VEC.push_back(std::to_string(game_player->GetPlayerTotalPoints()));

		if (game_player->isPlayerNew()) {
			player_points->insert(TableEntry(game_player->GetPlayerUserName(), points_temp_VEC));
		}
		else {
			ktp::DataBaseTable::iterator locatedTableEntry = player_points->find(game_player->GetPlayerUserName());
			locatedTableEntry->second = points_temp_VEC;
		}
	}
	//====

	int current_choice = 0;
	ktp::UInt menuchoice;

	FString txt_DisplayLeaderboardMenu("                    1. Next\n");
			txt_DisplayLeaderboardMenu += "                    2. Previous\n";
			txt_DisplayLeaderboardMenu += "                    3. Return to menu\n\n";

	do {
		txt_StandardGameScreenHeader();

		switch (current_choice) {
		case 0: 
			//Display the Total points leaderboard
			output << "                          Total points leaderboard\n";
			output << "                         **************************\n\n";
			txt_Leaderboard(5);
			break;
		case 1:
			//Display the Tutorial points leaderboard
			output << "                        Tutorial points leaderboard\n";
			output << "                       *****************************\n\n";
			txt_Leaderboard(4);
			break;
		case 2:
			//Display the Antonym points leaderboard
			output << "                        Antonym points leaderboard\n";
			output << "                       ****************************\n\n";
			txt_Leaderboard(0);
			break;
		case 3:
			//Display the Synonym points leaderboard
			output << "                        Synonym points leaderboard\n";
			output << "                       ****************************\n\n";
			txt_Leaderboard(2);
			break;
		case 4:
			//Display the Homonym points leaderboard
			output << "                        Homonym points leaderboard\n";
			output << "                       ****************************\n\n";
			txt_Leaderboard(1);
			break;
		case 5:
			//Display the Mystry points leaderboard
			output << "                        Mystery points leaderboard\n";
			output << "                       ****************************\n\n";
			txt_Leaderboard(3);
			break;
		}

		output << txt_DisplayLeaderboardMenu;
		output << "                    Enter your choice...";
		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			
			//The user wants to move to the next leaderboard
			//However if the current choice is == 5
			
			if (current_choice == 5) {
				//We have to rap the leaderboards around
				current_choice = 0;
			}
			//Otherwise we can still move forward
			else {
				current_choice++;
			}
			
		}
		else if (menuchoice == 2){

			//The user wants to move backwards in the leaderboard scrolling
			//However if the current position is == 0 

			if (current_choice == 0) {
				
				//Then we have to wrap around to the last leaderboard
				current_choice = 5;
			}
			//Otherwise we can move back normally
			else {
				current_choice--;
			}
		}
	} while (menuchoice != 3);
}

void Leaderboard::txt_Leaderboard(const Point & position)
{
	FString txt_Alignment = "                               "; // Text for alignment;

	//This vector holds all the players username and the points that this leaderboard will show.
	std::vector<UsernamePointPair> playerspoints_VEC;
	
	//For all the players in the database
	for (ktp::DataBaseTable::iterator eachEntry = player_points->begin(); eachEntry != player_points->end(); eachEntry++) {
		playerspoints_VEC.push_back(UsernamePointPair(eachEntry->first, std::stoi((eachEntry->second)[position])));
	}

	//Sorting the points vector using the sort method created
	std::sort(playerspoints_VEC.begin(), playerspoints_VEC.end(),sortByDecendingPoints);

	int leadingPlayer = playerspoints_VEC.size() - 1;
	int tracker = 0;

	while ((leadingPlayer >= 0) && (tracker < 10)) {
		if ((playerspoints_VEC.at(leadingPlayer)).second != 0) {
			output << txt_Alignment << (playerspoints_VEC.at(leadingPlayer)).first << " => " << (playerspoints_VEC.at(leadingPlayer)).second << nxtln;
		}
		leadingPlayer--;
		tracker++;
	}

	output << nxtln << nxtln;
}

void Leaderboard::txt_StandardGameScreenHeader()
{
	ktp::KTP_Algo::ClearConsole();
	output << " **************************************************************************\n";
	output << "|Frogs&Flies                                     A Team_Alpha BC Production|\n";
	output << " **************************************************************************\n";

	if (game_player->isPlayerLoggedIn()) {
		output << " Currently logged in as: " << game_player->GetPlayerUserName();
		output << "\n\n";
	}
	else {
		output << "\n";
	}
}
