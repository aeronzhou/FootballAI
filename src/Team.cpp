#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color)
	: mBall(ball), mPitch(pitch), mColor(color),
	  mOpponent(nullptr), mControllingPlayer(nullptr), mSupportingPlayer(nullptr), 
	  mReceivingPlayer(nullptr), mPlayerClosestToBall(nullptr), mPlayers(std::vector<Player*>()) {}


void Team::onInitialize() 
{
	// Setup state machine
	//////////////////////////////////////////////////////////////////////////

	// Initialize players
	createPlayers();

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		// Initilize players' position, heading, etc.
		//(*it)->getSteering()->separationOn();
	}

}

void Team::onUpdate(double time_diff)
{
	this->mIsUpdatingAfterChange = (time_diff == 0);

	calculatePlayerClosestToBall();

	// Update StateMachine
	//mStateMachine->update();	

	dt::Node::onUpdate(time_diff);
}

void Team::createPlayers()
{
	// Generate players with PlayerManager
	if (getTeamColor() == RED)
	{

	}
	else 
	{

	}
}

Team::TeamColor Team::getTeamColor() const 
{ 
	return mColor; 
}

Pitch* Team::getPitch() const 
{ 
	return mPitch; 
}

Team* Team::getOpponent() const 
{ 
	return mOpponent; 
}

void Team::setOpponent(Team* opponent)
{
	mOpponent = opponent;
}

void Team::returnAllPlayersToHome()
{
	
}

void Team::calculatePlayerClosestToBall()
{

}