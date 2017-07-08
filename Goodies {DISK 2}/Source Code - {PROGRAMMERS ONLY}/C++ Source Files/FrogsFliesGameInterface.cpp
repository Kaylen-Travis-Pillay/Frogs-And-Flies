#include "FrogsFliesGameInterface.h"
#include <Windows.h>
#include <MMSystem.h>


FrogsFliesGameInterface::FrogsFliesGameInterface()
{
	//Initializing game database and tables
	frogsFliesDatabase = new ktp::KTP_Database();
	SetUpGameDataBase();

	//Setting up flags
	soundFlag = new bool(true);

	//Initializing game
	game = new Game_FrogsAndFlies(frogsFliesDatabase);
}

FrogsFliesGameInterface::~FrogsFliesGameInterface()
{
	delete frogsFliesDatabase;
	delete soundFlag;
	delete game;
}

void FrogsFliesGameInterface::RunGameSoftware()
{
	PlaySound(TEXT("Fantasy_Game_Background.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	system("Color 1A");

	//Display splash screen
	txt_DisplaySplashScreen();

	//Display main menu
	txt_GameInterfaceMenu();

	//Run game
	game->run_Game_FrogsAndFlies();

	//Display the credit screen
	//TODO: Display credit screen needs to be completed
}

void FrogsFliesGameInterface::SetUpGameDataBase()
{
	frogsFliesDatabase->LoadTableInto_DB("AntonymQ_TBL",6,"antonym_questions.csv");
	frogsFliesDatabase->LoadTableInto_DB("SynonymQ_TBL",6,"synonym_questions.csv");
	frogsFliesDatabase->LoadTableInto_DB("HomonymQ_TBL",6,"homonym_questions.csv");
	frogsFliesDatabase->LoadTableInto_DB("MystryQ_TBL",6,"mystry_questions.csv");
	frogsFliesDatabase->LoadTableInto_DB("PlayerDetails_TBL",3,"player_details.csv");
	frogsFliesDatabase->LoadTableInto_DB("PlayerLogin_TBL",2,"player_login.csv");
	frogsFliesDatabase->LoadTableInto_DB("PlayerPoints_TBL",7,"player_points.csv");
}

int FrogsFliesGameInterface::GetMenuOption(int max_option)
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

void FrogsFliesGameInterface::txt_StandardGameScreenHeader()
{
	ktp::KTP_Algo::ClearConsole();
	output << " **************************************************************************\n";
	output << "|Frogs&Flies                                     A Team_Alpha BC Production|\n";
	output << " **************************************************************************\n\n";
}

void FrogsFliesGameInterface::screen_PlainTextWindow(ktp::FString displayString)
{
	txt_StandardGameScreenHeader();

	output <<  displayString;

	output << "                     ...Press ENTER to go back....";

	ktp::FString disposable;
	std::getline(input, displayString);
}

void FrogsFliesGameInterface::txt_DisplaySplashScreen()
{
	//Displaying standard header

	txt_StandardGameScreenHeader();

	/*
		Console based implementation of the TextBased game's splash screen
	*/

	FString disposable;

	output <<  "  ========================== Frogs & Flies ===============================" << nxtln;
	output <<  "\n\n";
	output <<  "              __   __                              . '  '  .\n";
	output <<  "       /`\\  .( o)-( o).  /`\\                   . '            '  .\n";
	output <<  "      / , \\(  _______  )/ , \\             () .'\n";
	output <<  "  ___/ /_\\ /`\"-------\"`\\ /_\\ \\___        `()\n";
	output <<  "  `~//^\\~_`\\  <__ __>  /`_~/^\\\\~`\n";
	output <<  "         `~//^\\\\~`~//^\\\\~`\n";
	output <<  "\n";
	output <<  "  ==================== A Team_Alpha BC production ========================" << nxtln;

	output << nxtln << "\n                     Press ENTER to continue..." << nxtln;
	
	std::getline(input, disposable);
	input.clear();
	output << "\n\n" << nxtln;

	std::string welcome = "\t\t      Welcome to the game!\n\t\t      Have fun and enjoy :)";
	ktp::KTP_Algo::AutoTypeText(welcome, 5);
	std::cout << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
}

int FrogsFliesGameInterface::menu_MainGameInterfaceMenu(flag_AUTOTYPEFLAG flag = true)
{
	//Display standard game header
	txt_StandardGameScreenHeader();

	//A short description of the game. This will be further explained in menus later.
	ktp::FString txt_Display1("                         Welcome to Frogs & Flies!\n");
	txt_Display1 += "          *********************************************************\n\n";
	txt_Display1 += "           Frogs & Flies is an open-source game (GNU) educational\n";
	txt_Display1 += "           game that helps players with English. The tutorials are\n";
	txt_Display1 += "           there to be a fun learning enviroment with the real\n";
	txt_Display1 += "           challenge being the game. CAUTION! Don't let the cute\n";
	txt_Display1 += "           name and simplistic game-player fool you, Frogs & Flies\n";
	txt_Display1 += "           is NOT for the fait hearted. Whether its challenging the\n";
	txt_Display1 += "           top players for a spot on the leader board or trying to\n";
	txt_Display1 += "           beat on of the three difficulty level, the end goal is\n";
	txt_Display1 += "           to reach the MYSTERY LEVEL.\n\n";
	txt_Display1 += "           Good luck and have fun!\n";
	txt_Display1 += "           Team_Alpha BC\n";
	txt_Display1 += "          ********************************************************\n\n";

	//We don't autotype if the flag is set to false
	if (flag) { ktp::KTP_Algo::AutoTypeText(txt_Display1, 5); }
	else { output << txt_Display1; }


	//Displaying menu application
	output << "                          Game Interface Menu:" << nxtln;
	output << "                         **********************" << nxtln;
	output << "                          1. Go to Game" << nxtln;
	output << "                          2. About Frogs & Flies" << nxtln;
	output << "                          3. About Developers" << nxtln;
	output << "                          4. Toggle Sound {ON/OFF}" << nxtln;
	output << nxtln;
	output << "                          Enter your choice here...";

	//Getting the users choice
	ktp::UInt numberOfMenuChoices = 4;
	int userMenuChoice = GetMenuOption(numberOfMenuChoices);

	return userMenuChoice;
}

void FrogsFliesGameInterface::txt_GameInterfaceMenu()
{
	/*
		The following text is used in the menu display windows
	*/
	
	//About Frogs & Flies display string
	ktp::FString txt_DisplayAboutFF("          *****************************************************\n");
	             txt_DisplayAboutFF += "          *              About Frogs & Flies                  *\n";
	             txt_DisplayAboutFF += "          *             *********************                 *\n";
				 txt_DisplayAboutFF += "          *                                                   *\n";
				 txt_DisplayAboutFF += "          * Frogs & Flies was built as part of the final year *\n";
				 txt_DisplayAboutFF += "          * major project of the developers. The game's first *\n";
				 txt_DisplayAboutFF += "          * and foremosts goal is to impart English skill     *\n";
				 txt_DisplayAboutFF += "          * that will help the user grow both parts of speech *\n";
				 txt_DisplayAboutFF += "          * and vocabulary of the player.                     *\n";
				 txt_DisplayAboutFF += "          *                                                   *\n";
				 txt_DisplayAboutFF += "          * A major focus of the game is the concept of point *\n";
				 txt_DisplayAboutFF += "          * and inspiring competion between players to get to *\n";
				 txt_DisplayAboutFF += "          * the top of different leader boards.               *\n";
				 txt_DisplayAboutFF += "          *                                                   *\n";
				 txt_DisplayAboutFF += "          * Frogs & Flies is fully open-source and follows    *\n";
				 txt_DisplayAboutFF += "          * the GNU public licence terms and conditions. The  *\n";
				 txt_DisplayAboutFF += "          * licence is distributed with the game as a PDF,    *\n";
				 txt_DisplayAboutFF += "          * and part of this licence allows you to freely use *\n";
				 txt_DisplayAboutFF += "          * , customise and distribute the game. We do ask    *\n";
				 txt_DisplayAboutFF += "          * however that the parts of the game that do not    *\n";
				 txt_DisplayAboutFF += "          * change are given credit to the author.            *\n";
				 txt_DisplayAboutFF += "          *                                                   *\n";
				 txt_DisplayAboutFF += "          * Enjoy! :)                                         *\n";
				 txt_DisplayAboutFF += "          *                                                   *\n";
				 txt_DisplayAboutFF += "          *****************************************************\n";

    //About Developer display string
	ktp::FString txt_DisplayAboutD("          *****************************************************\n");
	     		 txt_DisplayAboutD += "          *                 About Developers                  *\n";
				 txt_DisplayAboutD += "          *                ******************                 *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
		         txt_DisplayAboutD += "          *          The Developers of Team_Alpha BC          *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Kaylen Travis Pillay                         *\n";
				 txt_DisplayAboutD += "          *      \"Computer science is no more about computers *\n";
				 txt_DisplayAboutD += "          *       than astronomy is about telescopes.\"        *\n";
			     txt_DisplayAboutD += "          *                                  -Edsger Dijkstra *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Mpilwenhle Maphanga                          *\n";
				 txt_DisplayAboutD += "          *      \"Humility, in life, goes a long way\"         *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Kimyran Chetty                               *\n";
				 txt_DisplayAboutD += "          *      \"Quote here\"                                 *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Theolin Naidoo                               *\n";
				 txt_DisplayAboutD += "          *      \"An aspiring software developer\"             *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Justin Mahabeer                              *\n";
				 txt_DisplayAboutD += "          *      \"Quote here\"                                 *\n";
				 txt_DisplayAboutD += "          *                                                   *\n";
				 txt_DisplayAboutD += "          * [+]- Bathande Ndaba                               *\n";
			     txt_DisplayAboutD += "          *      \"Quote here\"                                 *\n";
				 txt_DisplayAboutD += "          *****************************************************\n";

	//*******************************************************************************************

	//Display the main menu which returns the menu choice
	int userMenuChoice;
	userMenuChoice = menu_MainGameInterfaceMenu();

	//while the users choice is not to continue to the game
	while (userMenuChoice != OPTION_1) {
		//If the user chooses About Frogs & Flies
		if (userMenuChoice == OPTION_2) {
			screen_PlainTextWindow(txt_DisplayAboutFF);
			input.ignore().get();
		}
		//Otherwise the users option would be about develepers option
		else if (userMenuChoice == OPTION_3) {
			screen_PlainTextWindow(txt_DisplayAboutD);
			input.ignore().get();
		}
		else {
			if (*soundFlag) {
				PlaySound(NULL, 0, 0);
				*soundFlag = false;
			}
			else {
				PlaySound(TEXT("Fantasy_Game_Background.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
				*soundFlag = true;
			}
		}

		userMenuChoice = menu_MainGameInterfaceMenu(false);
	}
}


