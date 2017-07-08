#pragma once
#include "Player.h"

/*
	File Name: Tutorial.h
	Date     : 10/04/2017
	Author   : Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This header file is responsable for running the tutorials
			   used in the game. Note that these are textbased tutorials
			   and the player is directed to online videos for an extended 
			   tutorial.

			   NB: If the player does not have an internet connection, 
			   Offline versions of the videos can be found on DISK 2 (GOODIES).

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


class Tutorial {

public:
//===Constructor/Destructor===
	/*
		This is the default constructor for the tutorial
	*/
	Tutorial(Player*);

	/*
		Note that this class does not contain a deconstructor because
		the the dynamic memory allocation for the variables used here
		"game_player" is handled in another class.
	*/

	Flag Run_Tutorial();

private:
//===Attributes===
	Player* game_player;

//===Text-based methods===

	//This is the game's screen header
	void txt_StandardGameScreenHeader();

	//This is the tutorial menu
	Flag menu_TutorialMenu();

//===Tutorial methods===

	void Run_AntonymTut();

	void Run_HomonymTut();

	void Run_SynonymTut();
};