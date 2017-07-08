#include "Game_FrogsAndFlies.h"

Game_FrogsAndFlies::Game_FrogsAndFlies(ktp::KTP_Database * database_PTR)
{
	//Initilizaing the database
	frogsFliesDatabase = database_PTR;
	player_Details = frogsFliesDatabase->GetDataBaseTable("PlayerDetails_TBL");
	player_LoginDetails = frogsFliesDatabase->GetDataBaseTable("PlayerLogin_TBL");
	player_points = frogsFliesDatabase->GetDataBaseTable("PlayerPoints_TBL");
	Antonym_Question = frogsFliesDatabase->GetDataBaseTable("AntonymQ_TBL");
	Synonym_Question = frogsFliesDatabase->GetDataBaseTable("SynonymQ_TBL");
	Homonym_Questions = frogsFliesDatabase->GetDataBaseTable("HomonymQ_TBL");
	Mystry_Questions = frogsFliesDatabase->GetDataBaseTable("MystryQ_TBL");

	Login_Suggestions_VEC = ktp::KTP_Algo::LoadTextFileData("Login_Suggestions.txt");
	players_Usernames_VEC = GetUsernamesFromDatabase();

	//Setting up the game's player
	game_player = new Player();
}

Game_FrogsAndFlies::~Game_FrogsAndFlies()
{
	delete players_Usernames_VEC;
	delete player_Details;
	delete player_LoginDetails;
	delete player_points;
	delete Antonym_Question;
	delete Homonym_Questions;
	delete Synonym_Question;
	delete Mystry_Questions;
	delete Login_Suggestions_VEC;
	delete game_player;
}

void Game_FrogsAndFlies::run_Game_FrogsAndFlies()
{
	menu_PlayerProfile();

	game_player->SetPlayerLoggedIn();

	txt_LoadingScreen();

	Tutorial tutorial(game_player);

	do{
		menu_InGameMenu();
	} while (!tutorial.Run_Tutorial());

	Game_Builder game_instance(game_player,frogsFliesDatabase);

	while (game_instance.Run_Game_Builder()) {
		menu_InGameMenu();
	}
}

void Game_FrogsAndFlies::txt_StandardGameScreenHeader()
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

void Game_FrogsAndFlies::txt_LoadingScreen()
{
	txt_StandardGameScreenHeader();

	output << *game_player;

	output << "                              Loading game\n";
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void Game_FrogsAndFlies::txt_HelpScreen()
{
	

	FString txt_DisplayHelpString("                               Game Help\n");
			txt_DisplayHelpString += "                              ***********\n\n";
			txt_DisplayHelpString += "               Frogs and flies come packaged with a help guide.\n";
			txt_DisplayHelpString += "               There are both online help facilities and local\n";
			txt_DisplayHelpString += "               (on your computer!) help facilities. If you have\n";
			txt_DisplayHelpString += "               internet access we advise you to use our online\n";
			txt_DisplayHelpString += "               facility or if not, head on over to the PDF Manual.\n\n";

			txt_DisplayHelpString += "                           1. Take me online!\n";
			txt_DisplayHelpString += "                           2. Return to menu\n";

	int menuChoice;
	
	do {
		txt_StandardGameScreenHeader();

		output << txt_DisplayHelpString;

		ktp::KTP_Algo::GetValidInput(menuChoice);

		if (menuChoice == 1) {
			FString myURL = "start http://www.ktpsolutions.co.za/frogsfliesmanual/"; 
			system(std::string(myURL).c_str());
		}
		else if (menuChoice == 2){
			break;
		}
	} while (menuChoice != 1 && menuChoice != 2);
}

int Game_FrogsAndFlies::GetMenuOption(int max_option)
{
	int choice;
	ktp::KTP_Algo::GetValidInput(choice);

	//While the users input is within the range
	while (choice < 0 || max_option < choice) {
		output << "Sorry! That is an menu option does not exist, try again" << nxtln;
		output << "...";
		ktp::KTP_Algo::GetValidInput(choice);
	}
	return choice;
}

void Game_FrogsAndFlies::SetUpThisPlayerInfo(FString username)
{
	game_player->SetNewPlayerFlag(false);
	game_player->SetUserName(username);
	game_player->SetPlayerName(player_Details->at(username)[0]);
	game_player->SetPlayerSurname(player_Details->at(username)[1]);
	game_player->SetPlayerPoints(std::stoi(player_points->at(username)[0]), Player::ANTONYM);//!
	game_player->SetPlayerPoints(std::stoi(player_points->at(username)[1]), Player::HOMONYM);//!
	game_player->SetPlayerPoints(std::stoi(player_points->at(username)[2]), Player::SYNONYM);//!
	game_player->SetPlayerPoints(std::stoi(player_points->at(username)[3]), Player::MYSTRY);//!
	game_player->SetPlayerPoints(std::stoi(player_points->at(username)[4]), Player::TUTORIAL);//!
}

Game_FrogsAndFlies::LoginResult Game_FrogsAndFlies::loginSession()
{
	ktp::UInt number_of_chances = 3;
	ktp::UInt number_of_InvalidUsername = 0;
	
	FString input_Username;
	FString input_Password;

	FString txt_DisplayLogin("                         Existing Player Login\n");
			txt_DisplayLogin += "                        ***********************\n\n";

	
	do {
		txt_StandardGameScreenHeader();

		FString enter_keypress;

		output << txt_DisplayLogin;

		output << "                Username: ";
		ktp::KTP_Algo::GetValidInput(input_Username);

		output << "                Password: ";
		ktp::KTP_Algo::GetValidInput(input_Password);

		output << "\n                          Press ENTER to login";
		input.ignore().get();

		//If the username is valid
		if (is_ValidUsername(input_Username)) {

			//If the password is correct
			if (input_Password == player_LoginDetails->at(input_Username)[0]) {
				game_player->SetUserName(input_Username);
				game_player->SetPlayerPassword(input_Password);
				return SUCCESS;
			}
			//Otherwise the pasword entered is incorrect
			else {
				number_of_chances--;
				output << "\n        ***ERROR: Incorrect Password! " << number_of_chances << " attemps remaining***";
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
		//Otherwise the username does not exist
		else {
			number_of_InvalidUsername++;
			output << "\n        ***ERROR: That username DOES NOT EXIST!***";
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

	} while (number_of_chances > 0 && number_of_InvalidUsername < 4);

	if (number_of_chances <= 0) {
		return FAILED;
	}
	else {
		return TIMED_OUT;
	}
}

Flag Game_FrogsAndFlies::is_ValidUsername(FString username)
{
	if (player_LoginDetails->find(username) != player_LoginDetails->end()) {
		return true;
	}
	else {
		return false;
	}
}

void Game_FrogsAndFlies::menu_PlayerProfile()
{
	//Menu string

	FString menu_STR("                         PLAYER PROFILE MENU                              \n");
			menu_STR += "                        *********************                             \n";
			menu_STR += "                                                                          \n";
			menu_STR += "                        1. Create a new profile                           \n";
			menu_STR += "                        2. Load a profile                                 \n";
			menu_STR += "                        3. Play game as GUEST                             \n";
			menu_STR += "                           {NB: Your progress will not be saved!!!}       \n";
			menu_STR += "                                                                          \n";
			menu_STR += "                                                                          \n";
			menu_STR += "                        Enter your choice...";

	//****

	// While the user has not successfully completed an option, continue displaying this menu
	
	int numberOfMenuOptions = 3;
	Flag is_Complete = false;

	do {
		txt_StandardGameScreenHeader();

		output << menu_STR;

		int userMenuChoice = GetMenuOption(numberOfMenuOptions);

		if (userMenuChoice == OPTION_1) {
			is_Complete = run_NewProfile();
		}
		else if (userMenuChoice == OPTION_2) {
			is_Complete = run_LoadExistingProfile();
		}
		else {
			is_Complete = run_GuestPlayer();
		}

	} while (!is_Complete);
}

Flag Game_FrogsAndFlies::run_NewProfile()
{
	//Variable
	
	FString player_NAME;
	FString player_SURNAME;
	FString player_USERNAME;
	FString player_PASSWORD;

	//****

	txt_StandardGameScreenHeader();

	output << "                         NEW PLAYER PROFILE\n";
	output << "                        ********************\n";

	output << "               NAME: ";
	ktp::KTP_Algo::GetValidInput(player_NAME);

	output << "            SURNAME: ";
	ktp::KTP_Algo::GetValidInput(player_SURNAME);

	do {
		txt_StandardGameScreenHeader();

		output << "                         NEW PLAYER PROFILE\n";
		output << "                        ********************\n";
		output << "               NAME: " << player_NAME;
		output << "\n            SURNAME: " << player_SURNAME;

		output << "\n                  { YOUR USERNAME MUST BE UNIQUE }\n";

		//Generate suggestions

		LoginSuggestionOptions_VEC options = GenerateUsernameOptions();
		FString suggestion_STR = "        Suggestions: " + options[0] + ", " + options[1] + ", " + options[2];
		output << suggestion_STR << nxtln;
		
		output << "           USERNAME: ";
		ktp::KTP_Algo::GetValidInput(player_USERNAME);

		if (is_Username_Available(player_USERNAME)) {
			output << "\n ERROR: That username already exists! Please enter another username";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			continue;

		}
		else {
			output << "           PASSWORD: ";
			ktp::KTP_Algo::GetValidInput(player_PASSWORD);
			break;
		}

	} while (true);
	
	//Setting up game_player
	
	game_player->SetPlayerName(player_NAME);
	game_player->SetPlayerSurname(player_SURNAME);
	game_player->SetUserName(player_USERNAME);
	game_player->SetPlayerPassword(player_PASSWORD);
	game_player->SetNewPlayerFlag(true);
	game_player->SetGuestPlayerFlag(false);

	game_player->SetPlayerPoints(0,Player::ANTONYM);//!
	game_player->SetPlayerPoints(0, Player::HOMONYM);//!
	game_player->SetPlayerPoints(0, Player::SYNONYM);//!
	game_player->SetPlayerPoints(0, Player::MYSTRY);//!
	game_player->SetPlayerPoints(0, Player::TUTORIAL);//!

	return true;
}

ktp::TextFileContainer_VEC * Game_FrogsAndFlies::GetUsernamesFromDatabase()
{
	ktp::TextFileContainer_VEC* returnContainer = new ktp::TextFileContainer_VEC();

	for (ktp::DataBaseTable::iterator eachEntry = player_Details->begin(); eachEntry != player_Details->end(); eachEntry++) {
		returnContainer->push_back(eachEntry->first);
	}

	return returnContainer;
}

Flag Game_FrogsAndFlies::is_Username_Available(FString username)
{
	//If the username does not exist!
	if (std::find(players_Usernames_VEC->begin(), players_Usernames_VEC->end(), username) != players_Usernames_VEC->end()) {
		return true;
	}
	//Otherwise
	else {
		return false;
	}
}

LoginSuggestionOptions_VEC Game_FrogsAndFlies::GenerateUsernameOptions()
{
	//Used to generate different random numbers every time the program is run
	srand(time(NULL));

	//Shuffles the login suggestions database table
	std::random_shuffle(Login_Suggestions_VEC->begin(), Login_Suggestions_VEC->end());

	//Variables
	LoginSuggestionOptions_VEC return_Options;
	Flag b_SuccessfulOption;
	ktp::UInt random_index;
	ktp::UInt number_of_options = 3;
	ktp::UInt loop_counter = 0;
	FString option;

	//While the number of unique options are not full, continue to get a unique option
	//NOTE: A for look could have been used here! Look into improving this in next version
	do {
		random_index = rand() % Login_Suggestions_VEC->size();
		option = Login_Suggestions_VEC->at(random_index);
		b_SuccessfulOption = (!is_Username_Available(option));

		if (b_SuccessfulOption) {
			return_Options.push_back(option);
			loop_counter++;
		}
	} while (loop_counter < number_of_options);

	return return_Options;
}

Flag Game_FrogsAndFlies::run_LoadExistingProfile()
{
	LoginResult login_result = loginSession(); 

	/*
		This method deals with the various results of the existing profile login
		status. If the player entered an incorrect password word too many times 
		they would have FAILED the login process and there account would be locked
		for 10 seconds. Otherwise if the player enters a username that does not
		exist in our database they will be returned the main player profile menu, and
		the login status would be TIMED_OUT. Finally all the details are correct and 
		can be moved to the game menu.
	*/
	
	if (login_result == FAILED) {
		
		txt_StandardGameScreenHeader();
		
		FString txt_DisplayWrongPassword("                  Your profile has been temporarily locked!\n\n");
				txt_DisplayWrongPassword += "            If you have forgotten your password do the following:\n";
				txt_DisplayWrongPassword += "              1. Give your teacher your username,\n";
				txt_DisplayWrongPassword += "              2. Write down the password your teacher gives you\n";
				txt_DisplayWrongPassword += "              3. Try loading your profile again\n\n";

		output << txt_DisplayWrongPassword;

		//Count down to unlock the account and return the user to the player profile screen

		ktp::UInt timeForLock = 20;

		for (ktp::UInt time = timeForLock; time > 0; time--) {
			output << "\r" << "	    Your account will be unlocked in " << time << " second(s)";
			
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		return false;

	}
	else if (login_result == TIMED_OUT) {
		txt_StandardGameScreenHeader();

		FString txt_DisplayInvalidUsername("            You have enter an invalid username too many times!\n");
				txt_DisplayInvalidUsername += "		  Are you sure you aren't a new user?\n\n";
				txt_DisplayInvalidUsername += "	     We are returning you to the player profile menu,\n";
				txt_DisplayInvalidUsername += "                    you may try again from there!\n\n";

		output << txt_DisplayInvalidUsername;

		ktp::UInt countdown = 3;

		for (ktp::UInt time = countdown; time > 0; time --) {
			output << "\r" << "                Returning to the Player Profile menu in " << time << " second(s)";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

		return false;
	}
	else {
		SetUpThisPlayerInfo(game_player->GetPlayerUserName());
		game_player->SetGuestPlayerFlag(false);
		return true;
	}

}

Flag Game_FrogsAndFlies::run_GuestPlayer()
{
	game_player->SetPlayerName("N/A");
	game_player->SetGuestPlayerFlag(true);
	game_player->SetNewPlayerFlag(false);
	game_player->SetPlayerSurname("N/A");
	game_player->SetUserName("GUEST");

	return true;

}

void Game_FrogsAndFlies::menu_InGameMenu()
{
	/*
		This method displays the ingame menu.
	*/

	//Variables
	
	Leaderboard currentLeaderBoard(player_points, game_player);
	int menu_choice;

	//****

	FString txt_DisplayInGame("                              InGame Menu\n");
			txt_DisplayInGame += "                             *************\n\n";
			txt_DisplayInGame += "                          1. Continue to game\n";
			txt_DisplayInGame += "                          2. Leaderboard\n";
			txt_DisplayInGame += "                          3. Help\n";
			txt_DisplayInGame += "                          4. Save & Exit\n\n";

	

	do {
		//Displaying the text for this menu
		txt_StandardGameScreenHeader();
		output << txt_DisplayInGame;
		output << "                       Enter your choice...";
		ktp::KTP_Algo::GetValidInput(menu_choice);

		//***

		if (menu_choice == OPTION_2) {
			currentLeaderBoard.run_Leaderboards();
		}
		else if (menu_choice == OPTION_3) {
			txt_HelpScreen();
		}
		else if (menu_choice == OPTION_4){
			SaveAndExit();
			break;
		}

	} while (menu_choice != OPTION_1);
}

void Game_FrogsAndFlies::SaveAndExit()
{
	if (!game_player->isPlayerGuest()) {
		LocalDatabaseSave();
		frogsFliesDatabase->SaveDataBaseTable("PlayerPoints_TBL","player_points.csv");
		frogsFliesDatabase->SaveDataBaseTable("PlayerLogin_TBL","player_login.csv");
		frogsFliesDatabase->SaveDataBaseTable("PlayerDetails_TBL", "player_details.csv");
	}

	txt_StandardGameScreenHeader();

	output << R"(
              ____                               __  _______       
             / _________ ___ ____   ___ ____ ___/ / / __/ (____ ___
            / _// __/ _ / _ `(_-<  / _ `/ _ / _  / / _// / / -_(_-<
           /_/ /_/  \___\_, /___/  \_,_/_//_\_,_/ /_/ /_/_/\__/___/
                       /___/                                           
    )";

	output << R"(
    Team Members:
                             -> Kaylen
                             -> Theolin
                             -> Mpilo
                             -> Kimyran
                             -> Justin
                             -> Bathande

    Developed by Team_Alpha BC in 2017 as a major programming assignment

    Frogs and Flies is implemented using the c++ programming language,

    and was developed using Microsoft Visual Studio 2015. The game drew

    inspiration from the original game Word Frog. 


                        Thank you for playing!
    )";

	output << "\n";
	for (int countdown = 7; countdown >= 1; countdown --) {
		output << "\r" << "                  Game will terminate in " << countdown << " second(s)";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	exit(0);
}

void Game_FrogsAndFlies::LocalDatabaseSave()
{
	//Updating the players points
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

	//Updating the players details
	ktp::DetailsContainer_VEC details_temp_VEC;
	
	details_temp_VEC.push_back(game_player->GetPlayerName());
	details_temp_VEC.push_back(game_player->GetPlayerSurname());

	if (game_player->isPlayerNew()) {
		player_Details->insert(TableEntry(game_player->GetPlayerUserName(), details_temp_VEC));
	}
	else {
		ktp::DataBaseTable::iterator locatedTableEntry = player_Details->find(game_player->GetPlayerUserName());
		locatedTableEntry->second = details_temp_VEC;
	}

	//Updating the players login details
	ktp::DetailsContainer_VEC login_temp_VEC;

	login_temp_VEC.push_back(game_player->GetPlayerPassword());

	if (game_player->isPlayerNew()) {
		player_LoginDetails->insert(TableEntry(game_player->GetPlayerUserName(),login_temp_VEC));
	}

}
