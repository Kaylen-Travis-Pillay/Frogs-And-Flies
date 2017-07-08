#pragma once
#include "Player.h"
#include "KTPAlgo_Lib.h"
#include "Game_FrogsAndFlies.h"
#include <map>
#include <string>
#include <vector>

/*
	File Name: FrogsFliesGameInterface.h
	Date     : 10/04/2017
	Author   : Team_Alpha BC Member Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This is the header file for a FrogsFliesGameInterface 
			   class. This class creates an instance of the game software.
			   This basically serves as the central hub for all the activities
			   of the software. A distinction should be made from the GAME and
			   the SOFTWARE. The SOFTWARE, which this class is a blueprint of,
			   is an entire instance of the entire Educational Software.The GAME
			   is the actual Questions and Answers - As outlined in the game 
			   documents.

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

typedef bool flag_AUTOTYPEFLAG;

class FrogsFliesGameInterface {

public:

//===Static Members===
	/*
		Static enum for options chosen by the player
	*/
	static enum MenuOptions {OPTION_1 = 1, OPTION_2 = 2, OPTION_3 = 3, OPTION_4 = 4} options;

//===Constructor/Deconstructor===
	/*
		Default game interface constructor. This class can be used to run the 
		entire software. The constructor sets up the Database for the software 
		that will be used throught other classes and makes sure that all files
		are present for the phase.
	*/
	FrogsFliesGameInterface();

	~FrogsFliesGameInterface();

//===Operations===
	/*
		This method runs the software
	*/
	void RunGameSoftware();

private:

//===Attributes===
	//Database setup variables

	ktp::KTP_Database* frogsFliesDatabase;

	bool* soundFlag;

	//Game object creation
	Game_FrogsAndFlies* game;

//===Operations===
	/*
		SetUpGameDatabase sets up the database object with the required files 
		for this game:
			
			1.antonymQuestions.csv
			2.synonymQuestions.csv
			3.homonymQuestions.csv
			4.mystryQuestions.csv
			5.playerDetails.csv
			6.playerLoginDetails.csv
			7.playerPointsDetails.csv
	*/
	void SetUpGameDataBase();

	/*
		GetMenuOptions. This method gets a valid menu option from the user.
	*/
	int GetMenuOption(int);

//===Game Text methods and menus===
	
	/*
		This method prints the console header on tyhe screen when called.
	*/

	void txt_StandardGameScreenHeader();

	/*
		This method prints a static default window with the provided string
	*/

	void screen_PlainTextWindow(ktp::FString);

	/*
		This method displays the splash screen for the game
		DEF Splash Screen:
			'A splash screen is a graphical control element consisting of window containing an image,
			 a logo and the current version of the software. A splash screen usually appears while a 
			 game or program is launching.'

		NB: This is the console based version of the game and thus ASCII ART is used
		    instead of images.
	*/
	void txt_DisplaySplashScreen();

	/*
		This method runs the game interface menu. This menu will be the very first menu that the 
		player will be exposed to. The following menu options are displayed:
			
			OPTION_1 : Start Game
			OPTION_2 : About Frogs and Flies
			OPTION_3 : Developers Bio
			OPTION_4 : Settings Menu
	*/
	void txt_GameInterfaceMenu();

	/*
		This method performs the menu actions for the Game Interface
	*/
	int menu_MainGameInterfaceMenu(flag_AUTOTYPEFLAG);

};