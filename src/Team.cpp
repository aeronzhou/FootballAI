#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"
#include "PlayerManager.h"
#include "Goal.h"
#include "Constant.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
	  mOpponent(nullptr), mControllingPlayer(nullptr), mPlayers(std::vector<Player*>()) {}


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

	// Update StateMachine
	//mStateMachine->update();	

	dt::Node::onUpdate(time_diff);
}

void Team::createPlayers()
{
	// Generate players with PlayerManager
	if (getTeamColor() == RED)
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_01", 
			this, FieldPlayer::ATTACKER, 2)).get());

		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_02", 
			this, FieldPlayer::ATTACKER, 14)).get());

		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_03", 
			this, FieldPlayer::DEFENDER, 1)).get());
		
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_04", 
			this, FieldPlayer::DEFENDER, 13)).get());

		mPlayers.push_back((GoalKeeper*)addChildNode(PlayerManager::get().createGoalKeeper("Red_05", 
			this, 6)).get());

		for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
		{
			(*it)->placeAtPosition((*it)->getPositionWithRegion(), RED_TEAM_HEADING, 0.15f);
			// Push it to the player list
			(*it)->push_back(*it);
		}
	}
	else 
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_01", 
			this, FieldPlayer::ATTACKER, 3)).get());

		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_02", 
			this, FieldPlayer::ATTACKER, 15)).get());

		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_03", 
			this, FieldPlayer::DEFENDER, 4)).get());

		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_04", 
			this, FieldPlayer::DEFENDER, 16)).get());

		mPlayers.push_back((GoalKeeper*)addChildNode(PlayerManager::get().createGoalKeeper("Blue_05", 
			this, 11)).get());

		for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
		{
			(*it)->placeAtPosition((*it)->getPositionWithRegion(), BLUE_TEAM_HEADING, 0.15f);
			(*it)->push_back(*it);
		}

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
