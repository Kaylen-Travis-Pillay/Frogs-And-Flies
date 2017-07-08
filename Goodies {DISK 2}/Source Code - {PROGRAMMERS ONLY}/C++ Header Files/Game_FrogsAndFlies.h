#pragma once
#include "Game_Builder.h"
#include "KTPAlgo_Lib.h"
#include "Player.h"
#include "Leaderboard.h"
#include "Tutorial.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

/*
	File Name: Game_FrogsAndFies.h
	Date     : 10/04/2017
	Author   : Team_Alpha BC Member Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This header file is the game central. This is where the player 
	           is logged in and all saving to the database (KTPDatabase) 
			   is done. This, along with other features like help menus 
			   and leaderboard paging display is done here. This is an 
			   important class as the player is constantly returned to 
			   the InGame menu during the game play!

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


typedef bool Flag;
typedef std::vector<FString> LoginSuggestionOptions_VEC;
typedef std::pair<FString, std::vector<FString>> TableEntry;

class Game_FrogsAndFlies {

public:

//===Static Members===
	/*
	Static enum for options chosen by the player
	*/
	static enum MenuOptions { OPTION_1 = 1, OPTION_2 = 2, OPTION_3 = 3, OPTION_4 = 4 } options;
	static enum LoginResult { FAILED, TIMED_OUT, SUCCESS} results;

//===Constructor/Destructor===
	/*
		This is the classes constructor that takes in a database pointer.
		This database is defined in the "KTPAlgo_Library" library.
	*/
	Game_FrogsAndFlies(ktp::KTP_Database*);

	~Game_FrogsAndFlies();

//===Operations===

	/*
		This method runs the entire game, including all menus and the
		player login
	*/
	void run_Game_FrogsAndFlies();


private:
//===Attributes===

	//Setting up the database tables
	ktp::KTP_Database* frogsFliesDatabase;
	ktp::DataBaseTable* player_LoginDetails;
	ktp::DataBaseTable* player_Details;
	ktp::DataBaseTable* player_points;
	ktp::DataBaseTable* Antonym_Question;
	ktp::DataBaseTable* Synonym_Question;
	ktp::DataBaseTable* Homonym_Questions;
	ktp::DataBaseTable* Mystry_Questions;

	ktp::TextFileContainer_VEC* Login_Suggestions_VEC;
	ktp::TextFileContainer_VEC* players_Usernames_VEC;

	//Defining the player class
	Player* game_player;

//===Operations===
	//****Text-based methods

	void txt_StandardGameScreenHeader();

	void txt_LoadingScreen();

	/*
		This screen will be used to display the help page, or rather
		to direct the user to the online help facilities
	*/

	void txt_HelpScreen();

	//****Helper functions

	int GetMenuOption(int);

	void SetUpThisPlayerInfo(FString username);

	LoginResult loginSession();

	Flag is_ValidUsername(FString username);



	//****Player profile acquisition
	/*
		This method runs the player profile menu. By the end of this menu
		the game player will be set up.
		The options that the player has is:
			1. Create new player profile
			2. Load player profile
			3. Play game as a guest {NB: Your progress will not be saved!!!}
	*/
	void menu_PlayerProfile();

	//*****New player profile methods
	/*
		This method runs the new profile option
	*/
	Flag run_NewProfile();

	/*
		This method creates a TextFileContainer_VEC with all the usernames that are
		stored in the database table player_Details
	*/
	ktp::TextFileContainer_VEC* GetUsernamesFromDatabase();

	/*
		Thie method checks whether a username is available
	*/
	Flag is_Username_Available(FString username);

	/*
		This method generates three unique usernames from the suggestions database
	*/
	LoginSuggestionOptions_VEC GenerateUsernameOptions();

	//*****Load Existing profile methods
	/*
		This method runs the load existing profile option, which will allow
		a user to load there previous save state.
	*/
	Flag run_LoadExistingProfile();

	//*****Guest player option
	Flag run_GuestPlayer();



	/*
		This section deals with the ingame menu
			1. Leaderboards
			2. Game contols
			3. Continue to game
			4. Save and Exit
	*/

	void menu_InGameMenu();

	/*
		Save And Exit. This method saves the player's details that have been added to
		the database. This commits the locally in-game save to the hdd. This also 
		returns the player to the credit screen.
	*/
	void SaveAndExit();

	/*
		Local update of player details to the database tables
	*/
	void LocalDatabaseSave();
};