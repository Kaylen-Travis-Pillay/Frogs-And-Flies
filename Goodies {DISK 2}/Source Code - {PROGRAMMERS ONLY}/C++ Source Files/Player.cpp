#include "Player.h"

Player::Player()
{
	//Dynamically allocates memory for the Players Attributes
	
	//FString Allocations
	player_username = new FString();
	player_name = new FString();
	player_surname = new FString();
	player_password = new FString();

	//Points Allocations
	player_points = new ktp::PointsContainer_VEC();

	//Badge allocation
	badges = new Badge_VEC();
	badges->push_back("NONE");
	badges->push_back("NONE");
	badges->push_back("NONE");
	badges->push_back("NONE");

	//Setting all these points to zero
	for (int position = 0; position < 5; position++) {
		player_points->push_back(0);
	}
	
	player_total_points = new Point(0);

	//Flag Allocations
	is_NewPlayer = new Flag();
	is_GuestPlayer = new Flag(false);
	is_player_loggedIn = false;

	//Resetting the Points to default
	ResetPlayerPointsState();
	
}

Player::~Player()
{
	delete player_name;
	delete player_password;
	delete player_username;
	delete player_points;
	delete player_surname;
	delete player_total_points;
	delete badges;
	delete is_NewPlayer;
	delete is_GuestPlayer;
}

void Player::SetPlayerPoints(const Point& points, PointType typeOfPoint)
{
	//If the total points are greater than or equal to the typeOfPoints then
	if (*player_total_points >= player_points->at(typeOfPoint)) {
		
		//Subtract old points from total
		*player_total_points -= player_points->at(typeOfPoint);

		/*
			We do this because when we are replacing the old points with new
			points the total player points must also reflect this change.
		*/
	}

	
	// Replacing old points with new points
	player_points->at(typeOfPoint) = points;

	// Adding the new points to the total points
	*player_total_points += points;
}

void Player::SetPlayerBadge(const PointType & badge, const FString & p_badge)
{
	badges->at(badge) = p_badge;
}

void Player::IncrementPlayerPoints(const Point & points, PointType typeOfPoint)
{
	// Incrementing the correct type of point for this player
	player_points->at(typeOfPoint) += points;

	//Updating the total player points
	*player_total_points += points;
}

void Player::ResetPlayerPointsState()
{
	/*
		This method is used to set the default player up in the 
		constructor.
	*/

	SetPlayerPoints(0,TUTORIAL);
	SetPlayerPoints(0,HOMONYM);
	SetPlayerPoints(0,SYNONYM);
	SetPlayerPoints(0,ANTONYM);
	SetPlayerPoints(0,MYSTRY);

	*player_total_points = 0;
}

std::ostream & operator<<(std::ostream & outputStream, const Player & player)
{
	outputStream << " ======================= Current player stats =======================\n";
	outputStream << "\n Username: " << player.GetPlayerUserName() << std::endl;
	outputStream << " Name    : " << player.GetPlayerName() << std::endl;
	outputStream << " Surname : " << player.GetPlayerSurname() << std::endl;
	outputStream << "\n ======================== Points break down =========================\n";
	outputStream << "\n Synonym points : " << player.GetPlayerPoints()[Player::SYNONYM] << std::endl;
	outputStream << " Homonym points : " << player.GetPlayerPoints()[Player::HOMONYM] << std::endl;
	outputStream << " Antonym points : " << player.GetPlayerPoints()[Player::ANTONYM] << std::endl;
	outputStream << " Mystry points  : " << player.GetPlayerPoints()[Player::MYSTRY] << std::endl;
	outputStream << " Tutorial points: " << player.GetPlayerPoints()[Player::TUTORIAL] << std::endl;
	outputStream << " Total : " << player.GetPlayerTotalPoints() << std::endl;
	outputStream << "\n =============================== FIN ================================\n" << std::endl;

	return outputStream;
}
