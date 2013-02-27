#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"
#include "PlayerManager.h"
#include "Goal.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
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
		FieldPlayer* player_01 = (FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_01", this, FieldPlayer::ATTACKER, 5)).get();
		player_01->placeAtPosition(Ogre::Vector3(5, 1, -2), Ogre::Vector3(0.f, 0.f, 1.f), 0.2f);

		FieldPlayer* player_02 = (FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_02", this, FieldPlayer::ATTACKER, 10)).get();
		player_02->placeAtPosition(Ogre::Vector3(5, 1, 2), Ogre::Vector3(0.f, 0.f, 1.f), 0.2f);
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

Ball* Team::getBall() const
{
	return mBall;
}

Goal* Team::getGoal() const 
{
	return mGoal;
}

void Team::returnAllPlayersToHome()
{
	
}

void Team::calculatePlayerClosestToBall()
{

}