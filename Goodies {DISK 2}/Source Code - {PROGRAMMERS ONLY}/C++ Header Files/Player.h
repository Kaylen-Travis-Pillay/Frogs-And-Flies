#pragma once
#include <string>
#include <iostream>
#include "KTPAlgo_Lib.h"

/*
	File Name: Player.h
    Date     : 10/04/2017
	Author   : Team_Alpha BC Member Kaylen Travis Pillay
	Creation : COMP315 - Advanced Programming { Major Group Project }

	Details  : This is the header file for a Player class. A Player object will
	           be used as an abstraction of the player of the over all game. 
			   Various functions will be provided for reuse purposes and allowing
			   the demonstration of C++ concepts studied in this course.

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


/*
	A point that is earned by a player is an unsigned integer. Therefore for the 
	purpose of encapsulation and more clear code typedef is used here. Note also
	that other typedefs serve a similar purpose
*/
typedef unsigned int Point;
typedef std::string FString;
typedef bool Flag;
typedef std::vector<FString> Badge_VEC;


class Player {
	
public:

//===Enumernation for types of points===

	 static enum PointType {ANTONYM = 0, HOMONYM = 1, SYNONYM = 2, MYSTRY = 3, TUTORIAL = 4} pointType;

//===Constructor, Destructor===

	/*
		Default Constructor for the Player Class. This constructor sets the state of
		the player object to its default. i.e. Points will be set to zero.
	*/
	Player();

	/*
		Destructor for the Player Class. This destructor guarentees to free all dynamically
		allocated memory used in throught this class.
	*/
	~Player();

//===Mutators===

	void SetUserName(const FString& username) { *player_username = username; }
	
	void SetPlayerName(const FString& name) { *player_name = name; }

	void SetPlayerSurname(const FString& surname) { *player_surname = surname; };

	void SetPlayerPassword(const FString& password) { *player_password = password; };

	void SetNewPlayerFlag(const Flag& flag) { *is_NewPlayer = flag; }

	void SetGuestPlayerFlag(const Flag& flag) { *is_GuestPlayer = flag; }

	void SetPlayerLoggedIn() { is_player_loggedIn = true; }

	/* 
		Note that this function does NOT increment the already existing player points, but 
		rather it overwrites the points that exist in the player points array.
	*/
	void SetPlayerPoints(const Point&, PointType);

	void SetPlayerBadge(const PointType&, const FString&);

//===Assessors===
	
	FString GetPlayerUserName() const { return *player_username; }

	FString GetPlayerName() const { return *player_name; }

	FString GetPlayerSurname() const { return *player_surname; }

	FString GetPlayerPassword() const { return *player_password; }

	ktp::PointsContainer_VEC GetPlayerPoints() const { return *player_points; }

	FString GetPlayerBadge(PointType p_badges) const { return badges->at(p_badges); }

	Point GetPlayerTotalPoints() const { return *player_total_points; }

	Flag isPlayerLoggedIn() { return is_player_loggedIn; }

	Flag isPlayerGuest() { return *is_GuestPlayer; }

	Flag isPlayerNew() { return *is_NewPlayer; }

//===General Player Functions===

	void IncrementPlayerPoints(const Point&, PointType);

//===Operator Overloads===

	friend std::ostream& operator << (std::ostream& outputStream, const Player& player);


private:

	//===Attributes===

	FString* player_username;
	FString* player_name;
	FString* player_surname;
	FString* player_password;
	ktp::PointsContainer_VEC* player_points;
	Badge_VEC* badges;
	Point* player_total_points;
	Flag* is_NewPlayer;
	Flag* is_GuestPlayer;
	Flag is_player_loggedIn;

	//===Helper Operations===
	
	void ResetPlayerPointsState();

};