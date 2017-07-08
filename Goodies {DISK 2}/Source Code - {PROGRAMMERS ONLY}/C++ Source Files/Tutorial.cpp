#include "Tutorial.h"

Tutorial::Tutorial(Player * current_player)
{
	game_player = current_player;
}

Flag Tutorial::Run_Tutorial()
{
	return menu_TutorialMenu();
}

void Tutorial::txt_StandardGameScreenHeader()
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

Flag Tutorial::menu_TutorialMenu()
{

	ktp::FString txtDisplayTutMenu("                     Welcome to Tutorial Central!\n");
				txtDisplayTutMenu += "                    ******************************\n";
				txtDisplayTutMenu += "           Excited to get playing? That's great! However we\n";
				txtDisplayTutMenu += "           we want you to be fully prepared to take on the \n";
				txtDisplayTutMenu += "           challenge of the leaderboards. Learn, and perfect\n";
				txtDisplayTutMenu += "           your skills here before taking on the game. Each\n";
				txtDisplayTutMenu += "           tutorial is explained in words that are easy and \n";
				txtDisplayTutMenu += "           presented in a fun way! We even give you points just\n";
				txtDisplayTutMenu += "           for doing the tutorials :)\n\n";
				txtDisplayTutMenu += "           Oh! Almost forgot, if you've got an internet connection\n";
				txtDisplayTutMenu += "           we've got a secret...\n\n";
				txtDisplayTutMenu += "                          1. Antonym Tutorial\n";
				txtDisplayTutMenu += "                          2. Homonym Tutorial\n";
				txtDisplayTutMenu += "                          3. Synonym Tutorial\n";
				txtDisplayTutMenu += "                          4. Continue to game\n";
				txtDisplayTutMenu += "                          5. Return to menu\n\n";
				txtDisplayTutMenu += "                          Enter your choice...";

	
	int menu_choice;
	Flag b_continue;
	do {
		txt_StandardGameScreenHeader();
		output << txtDisplayTutMenu;
		ktp::KTP_Algo::GetValidInput(menu_choice);

		if (menu_choice == 1) {
			Run_AntonymTut();
			game_player->IncrementPlayerPoints(2,Player::TUTORIAL);
			b_continue = false;
		}
		else if (menu_choice == 2) {
			Run_HomonymTut();
			game_player->IncrementPlayerPoints(2, Player::TUTORIAL);
			b_continue = false;
		}
		else if (menu_choice == 3) {
			//Display the Synonym tutorial
			Run_SynonymTut();
			game_player->IncrementPlayerPoints(2, Player::TUTORIAL);
			b_continue = false;
		}
		else if (menu_choice == 4) {
			//Make sure that a player has done atleast one tutorial!
			if (game_player->GetPlayerPoints()[Player::TUTORIAL] != 0) {
				return true;
			}
			else {
				output << "\n           ***ERROR: You MUST complete atleast on tutorial to continue!";
				std::this_thread::sleep_for(std::chrono::seconds(3));
				b_continue = false;
			}
		}
		else if (menu_choice == 5) {
			//Return the player to the ingame menu
			return false;
		}
	} while (!b_continue);
}

void Tutorial::Run_AntonymTut()
{
	FString antonymTitle;
	antonymTitle += R"(
     ______  __   __  ______  ______  __   __  __  __  __    __  ______    
    /\  __ \/\ "-.\ \/\__  _\/\  __ \/\ "-.\ \/\ \_\ \/\ "-./  \/\  ___\   
    \ \  __ \ \ \-.  \/_/\ \/\ \ \/\ \ \ \-.  \ \____ \ \ \-./\ \ \___  \  
     \ \_\ \_\ \_\\"\_\ \ \_\ \ \_____\ \_\\"\_\/\_____\ \_\ \ \_\/\_____\ 
      \/_/\/_/\/_/ \/_/  \/_/  \/_____/\/_/ \/_/\/_____/\/_/  \/_/\/_____/ 
                                                                       
    )";

	FString dinosaur;
	dinosaur += R"(
                            .       .
                           / `.   .' \
                   .---.  <    > <    >  .---.
                   |    \  \ - ~ ~ - /  /    |
                    ~-..-~             ~-..-~
                \~~~\.'                    `./~~~/
                 \__/                        \__/
                  /                  .-    .  \
           _._ _.-    .-~ ~-.       /       }   \/~~~/
       _.-'q  }~     /       }     {        ;    \__/
      {'__,  /      (       /      {       /      `. ,~~|   .     .
       `''''='~~-.__(      /_      |      /- _      `..-'   \\   //
                   / \   =/  ~~--~~{    ./|    ~-.     `-..__\\_//_.-'
                  {   \  +\         \  =\ (        ~ - . _ _ _..---~
                  |  | {   }         \   \_\
                 '---.o___,'       .o___,'  
    )";

	FString mouse;
	mouse += R"(
                            ..----.._    _
                          .' .--.    "-.(O)_
               '-.__.-'"'=:|  ,  _)_ \__ . c\'-..
                            ''------'---''---'-"
    )";

	int menuchoice;

	do {
		txt_StandardGameScreenHeader();
		output << antonymTitle;
		output << "\n      Antonyms are words the are opposite in meaning! Say we have the\n";
		output << "      word LARGE, which describes something big like a Dinosaur\n";
		output << dinosaur;
		output << "\n     , then the opposite of that would be something small, like a mouse!\n";
		output << mouse;
		output << "\n     Remember to look out for words that are opposite when trying to\n";
		output << "     answer ANTONYM questions!\n\n";
		output << "                       1. Take to the online VIDEOS!\n";
		output << "                       2. Return to menu\n\n";
		output << "                       Enter your choice...";

		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			FString myURL = "start https://www.youtube.com/embed/DwmroClMtbQ";
			system(std::string(myURL).c_str());
		}
		else if (menuchoice == 2) {
			return;
		}

	} while (menuchoice != 1 && menuchoice != 2);

}

void Tutorial::Run_HomonymTut()
{
	FString txt_DisplayHomonymTitle;
	txt_DisplayHomonymTitle += R"(
     __  __  ______  __    __  ______  __   __  __  __  __    __  ______    
    /\ \_\ \/\  __ \/\ "-./  \/\  __ \/\ "-.\ \/\ \_\ \/\ "-./  \/\  ___\   
    \ \  __ \ \ \/\ \ \ \-./\ \ \ \/\ \ \ \-.  \ \____ \ \ \-./\ \ \___  \  
     \ \_\ \_\ \_____\ \_\ \ \_\ \_____\ \_\\"\_\/\_____\ \_\ \ \_\/\_____\ 
      \/_/\/_/\/_____/\/_/  \/_/\/_____/\/_/ \/_/\/_____/\/_/  \/_/\/_____/ 
                                                                        
    )";

	FString eye;
	eye += R"(
                               _ . - = - . _
                           . "  \  \   /  /  " .
                         ,  \                 /  .
                       . \   _,.--~=~"~=~--.._   / .
                      ;  _.-"  / \ !   ! / \  "-._  .
                     / ,"     / ,` .---. `, \     ". \
                    /.'   `~  |   /:::::\   |  ~`   '.\
                    \`.  `~   |   \:::::/   | ~`  ~ .'/
                     \ `.  `~ \ `, `~~~' ,` /   ~`.' /
                      .  "-._  \ / !   ! \ /  _.-"  .
                       ./    "=~~.._  _..~~=`"    \.
                         ,/         ""          \,
                          . _/             \_ . 
                             " - ./. .\. - "
 
    )";

	int menuchoice;

	do {
		txt_StandardGameScreenHeader();
		output << txt_DisplayHomonymTitle;
		output << "\n      Homonyms are words that sound the same, but have different meaning!\n";
		output << "      Say we have the word EYE, which refers to the organ we use to see with\n";
		output << eye;
		output << "\n    , then the Homonym of this word would be I, which refers to you,\n";
		output << "      like \"I am having fun!\"\n\n";
		output << "      Remember to look out for words that sound the same when trying to\n";
		output << "      answer Homonym questions!\n";
		output << "                       1. Take to the online VIDEOS!\n";
		output << "                       2. Return to menu\n\n";
		output << "                       Enter your choice...";

		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			FString myURL = "start https://www.youtube.com/embed/w7xxTqNL8DU?autoplay=1/";
			system(std::string(myURL).c_str());
		}
		else if (menuchoice == 2) {
			return;
		}

	} while (menuchoice != 1 && menuchoice != 2);
}

void Tutorial::Run_SynonymTut()
{
	int menuchoice;
	do {
		txt_StandardGameScreenHeader();
		output << R"(
 ______   __  __   __   __   ______   __   __   __  __   __    __   ______    
/\  ___\ /\ \_\ \ /\ "-.\ \ /\  __ \ /\ "-.\ \ /\ \_\ \ /\ "-./  \ /\  ___\   
\ \___  \\ \____ \\ \ \-.  \\ \ \/\ \\ \ \-.  \\ \____ \\ \ \-./\ \\ \___  \  
 \/\_____\\/\_____\\ \_\\"\_\\ \_____\\ \_\\"\_\\/\_____\\ \_\ \ \_\\/\_____\ 
  \/_____/ \/_____/ \/_/ \/_/ \/_____/ \/_/ \/_/ \/_____/ \/_/  \/_/ \/_____/ 
                                                                              

    Synonyms are words that are opposite in meaning. Let's take the word 
    SAD, when someone is not feeling good,

                  twoep   mkkkkkkk
                z1     ldk        Vtmn
               i   Cm    k        k   Tkm
              k   xk D     k        V     m
             yl                            m
              m                             m
               h                             l
                l            k        Y       k
                 p           yk       l       l
                  k   V     y  k      l        k
                   r 7h    z  l k     l        l
                    o `'   l 7   l     k        k
                     r  ' p  m   k    lmmmt      k
                     l  .l  m    k    l          km
                     l  r   k   Yh   y            k
                     2oP     k   t   tyyy         k
                       '  y  k   Dk      D        m
                         mm  m  V  mmmmyt         mn
                              Tyl t               m Ymmm
                 (---. ' __        r             mt     Yz
             (`--     `-'  )        mmm      mmlt  YMmmmmnnc
              -_    =    --        wwwwt       D
                >    =  (BP     mkT           Y
                ---______)    K          m mkT
                               Ym       y Y
                                 ym    m
                                    Ymm


    
    , then the Synonym of this would be HAPPY, when someone feels good

                            
                             OOOOOOOOOOO
                         OOOOOOOOOOOOOOOOOOO
                      OOOOOO  OOOOOOOOO  OOOOOO
                    OOOOOO      OOOOO      OOOOOO
                  OOOOOOOO  #   OOOOO  #   OOOOOOOO
                 OOOOOOOOOO    OOOOOOO    OOOOOOOOOO
                OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
                OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
                OOOO  OOOOOOOOOOOOOOOOOOOOOOOOO  OOOO
                 OOOO  OOOOOOOOOOOOOOOOOOOOOOO  OOOO
                  OOOO   OOOOOOOOOOOOOOOOOOOO  OOOO
                   OOOOO   OOOOOOOOOOOOOOO   OOOO
                     OOOOOO   OOOOOOOOO   OOOOOO
                        OOOOOO         OOOOOO
                             OOOOOOOOOOOO


             1. Take me to the online video
             2. Return to menu

        )";

		output << "\n                       Enter your choice...";

		ktp::KTP_Algo::GetValidInput(menuchoice);

		if (menuchoice == 1) {
			FString myURL = "start https://www.youtube.com/embed/txcxH3GYHXM";
			system(std::string(myURL).c_str());
		}
		else if (menuchoice == 2) {
			return;
		}
	} while (menuchoice != 1 && menuchoice != 2);
}
