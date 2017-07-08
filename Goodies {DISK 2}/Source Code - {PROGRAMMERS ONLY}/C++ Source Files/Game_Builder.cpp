#include "Game_Builder.h"

Game_Builder::Game_Builder(Player * player, ktp::KTP_Database * db)
{
	game_player = player;
	database = db;
	
	timing = new ktp::UInt();
	earnings = new ktp::Point();
	collectedEarnings = new ktp::Point();
	
	summary_VEC = new Q_A_Summary_VEC();

	questions_Answered = new ktp::UInt();
	correctly_Answered = new ktp::UInt();
	incorrectly_Answered = new ktp::UInt();
}

Game_Builder::~Game_Builder()
{
	DeleteState();
}

void Game_Builder::txt_StandardGameScreenHeader()
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

FString Game_Builder::PrintProgress(const int & percentage)
{
	/*
		This method prints a simple progress bar like so,
		[>>>>>>>>>>              ], this allows us to give 
		a visual representation of the amount of points a
		player has towards their next badge.
	*/

	FString fstring_builder = "           [";
	int printlevel = 50;
	
	for (int arrow = 0; arrow < (printlevel / 2); arrow++) 
	{
		
		if (arrow <= (percentage / 2)) 
		{
			
			if (percentage == 0)
			{ 
				// Do nothing
			}
			else 
			{
				fstring_builder += ">";
			}

		}
		else 
		{
			fstring_builder += " ";
		}

	}
	fstring_builder += "]";
	return fstring_builder;
}

void Game_Builder::DisplayBadgeProgressBar(const ktp::Point & points, const double & threshold)
{
	//Display the progress bar and the actual points reprentation
	ktp::UInt const constant = 50;
	output << std::setw(-5) << PrintProgress((points / threshold) * constant) << " " << points << "/" << threshold;
	output << " collected for next badge.";
}

void Game_Builder::BadgeStatus(ktp::Point points, Player::PointType type)
{
	//If the players points is less that the beginner badge threshold
	if (points < BEGINNER_BADGE) {
		DisplayBadgeProgressBar(points,BEGINNER_BADGE);
		output << "\n           Current Badge: No badges earned!\n";
	}
	//Otherwise if the players points are less that the Novice badge threshold
	else if (points < NOVICE_BADGE) {
		DisplayBadgeProgressBar(points, NOVICE_BADGE);
		output << "\n           Current Badge: BEGINNER\n";
		game_player->SetPlayerBadge(type, "BEGINNER");
	}
	//Otherwise if the players poinst are less than the Master badge threshold
	else if (points < MASTER_BADGE) {
		DisplayBadgeProgressBar(points, MASTER_BADGE);
		output << "\n           Current Badge: NOVICE\n";
		game_player->SetPlayerBadge(type, "NOVICE");
	}
	//Otherwise the player has reached there final badge!
	else if (points > MASTER_BADGE) {
		DisplayBadgeProgressBar(points, MASTER_BADGE);
		output << "\n           Current Badge: MASTER\n";
		game_player->SetPlayerBadge(type, "MASTER");
	}
	else {
		DisplayBadgeProgressBar(points, MASTER_BADGE);
		output << "\n           Current Badge: NOVICE\n";
		game_player->SetPlayerBadge(type, "NOVICE");
	}
}

Flag Game_Builder::canPlayMystery()
{
	FString antonymBadge = game_player->GetPlayerBadge(Player::ANTONYM);
	FString homonymBadge = game_player->GetPlayerBadge(Player::HOMONYM);
	FString synonymBadge = game_player->GetPlayerBadge(Player::SYNONYM);
	
	if (antonymBadge == "MASTER" && homonymBadge == "MASTER" && synonymBadge == "MASTER") {
		return true;
	}
	else {
		return false;
	}
}

void Game_Builder::DifficultyChoice(Player::PointType gametype)
{
	int menuchoice;
	do {
		txt_StandardGameScreenHeader();

		output << R"(
                What difficulty would you like to play?
               *****************************************

                 1. Easy {I'm just finding my feet}
                         - You get 60 Seconds
                         - 3 Points for a correct answer
                   
                 2. Medium {I'm getting better!}
                         - You get 35 Seconds
                         - 5 Points for a correct answer
                   
                 3. Hard {Bring it on...!}
                         - You get 15 Seconds
                         - 7 Points for a correct answer

                 4. Developers Mode {???}
			 - You get ??? Seconds
                         - ??? Points for a correct answer
                         - HINT: DON'T DO IT! HAHAHA

        )";

		output << "\n\n\n                     Enter your choice...";

	
		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			//Easy setting
			*earnings = 3;
			*timing = 60;
			break;
		}
		else if (menuchoice == 2) {
			//Medium setting
			*earnings = 5;
			*timing = 35;
			break;
		}
		else if (menuchoice == 3) {
			//Hard Setting
			*earnings = 7;
			*timing = 15;
			break;
		}
		else if (menuchoice == 4) {
			//Developers mode!

			if (game_player->GetPlayerBadge(gametype) == "MASTER") {
				std::srand(time(NULL));

				*timing = rand() % 15 + 1;
				*earnings = rand() % 15 + 1;

				break;
			}
			else {
				output << "                ***ERROR: You need a MASTER badge to play this difficulty";
				std::this_thread::sleep_for(std::chrono::seconds(3));
			}
		}
	} while (!false);

	
}

Flag Game_Builder::menu_GameCentral()
{
	int menuchoice;

	do {
		txt_StandardGameScreenHeader();

		output << R"(
              ____                               __  _______       
             / _________ ___ ____   ___ ____ ___/ / / __/ (____ ___
            / _// __/ _ / _ `(_-<  / _ `/ _ / _  / / _// / / -_(_-<
           /_/ /_/  \___\_, /___/  \_,_/_//_\_,_/ /_/ /_/_/\__/___/
                       /___/                                           


        Welcome to your hub! This is where you can keep track of your 
        progress and choose a game to take on! Earn those Master badges
        and try to beat the game. Remeber that you can go back and view
        the tutorials! Good luck young frog!

        )";

		output << "\n        1. Antonym mission\n";
		BadgeStatus(game_player->GetPlayerPoints()[Player::ANTONYM], Player::ANTONYM);

		output << "\n        2. Homonym mission\n";
		BadgeStatus(game_player->GetPlayerPoints()[Player::HOMONYM], Player::HOMONYM);

		output << "\n        3. Synonym mission\n";
		BadgeStatus(game_player->GetPlayerPoints()[Player::SYNONYM], Player::SYNONYM);

		if (canPlayMystery()) {
			output << "\n        4. Mystery mission\n";
			BadgeStatus(game_player->GetPlayerPoints()[Player::MYSTRY], Player::MYSTRY);
			output << "\n        5. Return to in game menu\n";
		}
		else {
			output << "\n        4. Return to in game menu\n";
		}

		

		output << "\n\n                       Enter your choice...";
		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			//Play game with antonym questions
			RunGame(Player::ANTONYM);

			GenerateSummary();

			//Increment Antonym points

			game_player->IncrementPlayerPoints(*collectedEarnings,Player::ANTONYM);

			//Reset state
			DeleteState();
			ResetState();
		}
		else if (menuchoice == 2) {
			//Play game with homonym questions
			RunGame(Player::HOMONYM);

			GenerateSummary();

			//Increment Homonym points

			game_player->IncrementPlayerPoints(*collectedEarnings, Player::HOMONYM);

			//Reset state
			DeleteState();
			ResetState();
		}
		else if (menuchoice == 3) {
			//Play game with synonym questions
			RunGame(Player::SYNONYM);

			GenerateSummary();

			//Increment Synonym points

			game_player->IncrementPlayerPoints(*collectedEarnings,Player::SYNONYM);

			//Reset state
			DeleteState();
			ResetState();
		}
		else if ((menuchoice == 4 || menuchoice == 5) && canPlayMystery()) {
			if (menuchoice == 4) {
				//Play game with mystery questions
				RunGame(Player::MYSTRY);

				GenerateSummary();

				//Increment Mystry points

				game_player->IncrementPlayerPoints(*collectedEarnings, Player::MYSTRY);

				//Reset state
				DeleteState();
				ResetState();
			}
			else if (menuchoice == 5) {
				//Return to game menu
				return true;
			}
		}
		else if ((menuchoice == 4 || menuchoice == 5) && !canPlayMystery()) {
			if (menuchoice == 4) {
				//Return to game menu;
				return true;
			}
		}
	} while (true);


}

void Game_Builder::RunGame(Player::PointType gametype)
{
	DifficultyChoice(gametype);

	//Intializing the timer 
	time_t initialTimer = time(NULL);

	//Setting the timer for using timing chosen at difficulty menu
	initialTimer = initialTimer + *timing;

	//Questions used in this current game

	ktp::DataBaseTable currentGameQuestions;

	switch (gametype)
	{
	case Player::ANTONYM:
		currentGameQuestions = *(database->GetDataBaseTable("AntonymQ_TBL"));
		break;
	case Player::HOMONYM:
		currentGameQuestions = *(database->GetDataBaseTable("HomonymQ_TBL"));
		break;
	case Player::SYNONYM:
		currentGameQuestions = *(database->GetDataBaseTable("SynonymQ_TBL"));
		break;
	case Player::MYSTRY:
		currentGameQuestions = *(database->GetDataBaseTable("MystryQ_TBL"));
		break;
	default:
		break;
	}

	//Shuffle the current game questions map using the template shuffle method created
	Q_n_A_PAIR Question_VEC = ktp::KTP_Algo::ShuffleMap<FString,Q_VEC>(currentGameQuestions);

	ktp::UInt question_Asked = 0;
	ktp::UInt _correctly_Answered = 0;
	ktp::UInt _incorrectly_Answered = 0;

	for (Q_n_A_PAIR::iterator each_question = Question_VEC.begin(); each_question != Question_VEC.end() && (time(NULL) < initialTimer); each_question++) {
		
		//Increment number of questions asked
		question_Asked++;

		txt_StandardGameScreenHeader();

		FString answer = RunGameRound(each_question,question_Asked,gametype);

		if (CheckAnswer(answer, each_question->second[0])) {
			_correctly_Answered++;
		}
		else {
			_incorrectly_Answered++;
			summary_VEC->insert(std::pair<FString,FString>(each_question->first,each_question->second[0]));
		}
	}

	*questions_Answered = question_Asked;
	*correctly_Answered = _correctly_Answered;
	*incorrectly_Answered = _incorrectly_Answered;

	if (*questions_Answered == currentGameQuestions.size()) {
		
		txt_StandardGameScreenHeader();
		output << "                          ROUND COMPLETE!\n";
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else {
		
		txt_StandardGameScreenHeader();
		output << R"(
                            Your time is up!
                         Let's see how you did 
        )";
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}

}

FString Game_Builder::RunGameRound(Q_n_A_PAIR::iterator asked_question, ktp::UInt question_number, Player::PointType gametype)
{
	do {
		std::srand(time(NULL));

		FString question = asked_question->first;
		Q_VEC answers = asked_question->second;

		output << "                          Question " << question_number << ":\n";
		output << "                         *************\n";

		std::random_shuffle(answers.begin(), answers.end());

		switch (gametype)
		{
		case Player::ANTONYM:
			output << "           What is the Antonym of the word " << question;
			break;
		case Player::HOMONYM:
			output << "           What is the Homonym of the word " << question;
			break;
		case Player::SYNONYM:
			output << "           What is the Synonym of the word " << question;
			break;
		default:
			output << "             What is the ??? of the word " << question;
			break;
		}

		output << nxtln << nxtln;

		output << "                          1. " << answers[0] << nxtln;
		output << "                          2. " << answers[1] << nxtln;
		output << "                          3. " << answers[2] << nxtln;
		output << "                          4. " << answers[3] << nxtln;
		output << "                          5. " << answers[4] << nxtln;

		output << "\n\n                       Enter your choice...";

		ktp::UInt options;
		ktp::KTP_Algo::GetValidInput(options);

		switch (options)
		{
		case 1:
			return answers[0];
		case 2:
			return answers[1];
		case 3:
			return answers[2];
		case 4:
			return answers[3];
		case 5:
			return answers[4];
		default:
			txt_StandardGameScreenHeader();
			break;
		}

	} while (!false);
	
}

Flag Game_Builder::CheckAnswer(FString given_answer, FString correct_answer)
{
	if (given_answer == correct_answer) {
		*collectedEarnings += *earnings;
		return true;
	}
	else {
		return false;
	}
}

void Game_Builder::GenerateSummary()
{
	ktp::UInt accuracyPercentage = ((double)(*correctly_Answered)/(double)(*questions_Answered)) * 100;

	txt_StandardGameScreenHeader();

	output << R"(
                               Round Summary
                              ***************
    )";

	output << "        Questions Asked: " << *questions_Answered << "\n";
	output << "            Correct Answers: " << *correctly_Answered << "\n";
	output << "          Incorrect Answers: " << *incorrectly_Answered << "\n";
	output << "              Points Scored: " << *collectedEarnings << "\n";
	output << "                  Accuracy : " << accuracyPercentage << " %\n\n";

	output << R"(
		          These are your corrections:
                          ---------------------------
            {Question you got wrong => Correct answer to that question}

    )";

	output << nxtln;

	for (Q_A_Summary_VEC::iterator summary_obj = summary_VEC->begin(); summary_obj != summary_VEC->end(); summary_obj++) {
		
		output << "                            " << summary_obj->first << " => " << summary_obj->second << nxtln;
	}

	output << "\n\n                           Press ENTER to continue";
	input.ignore().get();
}

void Game_Builder::DeleteState()
{
	delete questions_Answered;
	delete correctly_Answered;
	delete incorrectly_Answered;
	delete summary_VEC;
	delete timing;
	delete collectedEarnings;
	delete earnings;
}

void Game_Builder::ResetState()
{
	questions_Answered = new ktp::UInt(0);
	correctly_Answered = new ktp::UInt(0);
	incorrectly_Answered = new ktp::UInt(0);

	summary_VEC = new Q_A_Summary_VEC();

	timing = new ktp::UInt(0);
	earnings = new ktp::Point();
	collectedEarnings = new ktp::Point();

}


