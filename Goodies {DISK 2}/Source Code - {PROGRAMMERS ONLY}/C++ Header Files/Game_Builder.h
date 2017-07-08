#pragma once
#include "Player.h"
#include "KTPAlgo_Lib.h"
#include <iomanip>
#include <locale>
#include <time.h>

#define BEGINNER_BADGE 100.0
#define NOVICE_BADGE 700.0
#define MASTER_BADGE 1500.0
/*
	File Name: Game_Builder.h
	Date     : 10/04/2017
	Author   : Team_Alpha BC Member Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This header file handles the entire game play aspect of
	           the software. It is resposible for the running of game 
			   rounds, making sure to check the responses given to 
			   questions, give the user a summary of the round and
	           update the players points respectfully.

	Frogs & Flies Console game Copyright (C) 2017  Kaylen Travis Pillay

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


typedef std::vector<std::pair<FString, std::vector<FString>>> Q_n_A_PAIR;
typedef std::vector<std::string> Q_VEC;
typedef std::map<FString, FString> Q_A_Summary_VEC;

class Game_Builder {
	
public:
//===Constructor===

	// This is the constructor for the game builder class
	Game_Builder(Player*, ktp::KTP_Database*);

	~Game_Builder();

	/*
		This function runs the entire game play, checks answers and
		displays the summary to the player
	*/

	Flag Run_Game_Builder() { return menu_GameCentral(); }

private:
//===Attributes===

	Player* game_player;
	ktp::KTP_Database* database;
	ktp::Point* earnings;
	ktp::Point* collectedEarnings;
	ktp::UInt* timing;

	Q_A_Summary_VEC* summary_VEC;

	ktp::UInt* questions_Answered;
	ktp::UInt* correctly_Answered;
	ktp::UInt* incorrectly_Answered;

//===Helper Functions===

	void txt_StandardGameScreenHeader();
	
	//Creating the badge progress bar
	FString PrintProgress(const int&);
	
	//Displaying the badge progress bar with extra information.
	void DisplayBadgeProgressBar(const ktp::Point &, const double&);

	/*
		This method makes use of the above methods to display a user
		friendly badge status.
	*/
	void BadgeStatus(ktp::Point, Player::PointType);

	/*
		This method checks whether the user can infact play the mystery
		level or not!
	*/
	Flag canPlayMystery();

	void DifficultyChoice(Player::PointType);

//===Menus===

	//The game central menu
	Flag menu_GameCentral();

//===Functions===

	//This method runs one of four games
	void RunGame(Player::PointType);

	//This method runs a round of the game chosen, a round has a time limit
	FString RunGameRound(Q_n_A_PAIR::iterator, ktp::UInt, Player::PointType);

	//This function checks whether the users answer is correct or not
	Flag CheckAnswer(FString,FString);

	//This function generates a summary for the game
	void GenerateSummary();

	void DeleteState();

	void ResetState();
};