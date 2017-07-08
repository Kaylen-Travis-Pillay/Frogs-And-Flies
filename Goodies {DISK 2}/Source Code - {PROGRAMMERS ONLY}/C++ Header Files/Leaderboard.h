#pragma once
#include "KTPAlgo_Lib.h"
#include "Player.h"

/*
	File Name: Leaderboard.h
	Date     : 10/04/2017
	Author   : Team_Alpha BC Member Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This header file is resposible for the leaderboards. A Paging
	           techique has been used to "page" through leaderboards 
			   seamlessly. This leaderboard shows the top ten players 
			   in each catagory.

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


typedef std::pair<std::string, ktp::UInt> UsernamePointPair;
typedef std::pair<FString, std::vector<FString>> TableEntry;

class Leaderboard {

public:
//===Constructor===
	Leaderboard(ktp::DataBaseTable*, Player*);

	/*
		Note that this class does not contain a deconstructor because
		the the dynamic memory allocation for the variables used here
		"game_player" and "player_points" are handled in another class.
	*/

	void run_Leaderboards();

private: 
//===Attributes===
	ktp::DataBaseTable* player_points;
	Player* game_player;

//===Operations===
	
	//Leaderboard
	void txt_Leaderboard(const Point&);

	//General sort for leaderboards
	static Flag sortByDecendingPoints(const UsernamePointPair& a, const UsernamePointPair& b) { return (a.second < b.second); }

	//Text-based helper methods

	void txt_StandardGameScreenHeader();
};