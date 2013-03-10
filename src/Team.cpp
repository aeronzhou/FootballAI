#include "Team.h"
#include "Ball.h"
#include "Pitch.h"
#include "Player.h"
#include "FieldPlayer.h"
#include "GoalKeeper.h"
#include "PlayerManager.h"
#include "PlayerPositionManager.h"
#include "Goal.h"
#include "TeamState.h"
#include "Constant.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
	  mOpponent(nullptr), mControllingPlayer(nullptr), mPlayers(std::vector<Player*>()) {}


void Team::onInitialize() 
{
	// Setup state machine
	mStateMachine = new StateMachine<Team>(this);
	mStateMachine->setCurrentState(PositionalAttacking::get());	

	// Initialize players
	createPlayers();

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		// Initilize players' position, heading, etc.
		//(*it)->getSteering()->separationOn();
	}
}

void Team::onDeinitialize()
{
	delete mStateMachine;
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
	std::vector<int> vec_pos = PlayerPositionManager::get().getOriginPosition("WaitingForKickOff");

	// Generate players with PlayerManager
	if (getTeamColor() == RED)
	{
		for (int i = 0; i < 7; ++i)
		{
			// Attacker这个再来处理
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
				this, FieldPlayer::ATTACKER, vec_pos[i])).get());
			mPlayers.back()->placeAtPosition(mPlayers.back()->getPositionWithRegion(), RED_TEAM_HEADING, 0.15f);
		}
	}
	else 
	{
		for (int i = 7; i < 14; ++i)
		{
			// Attacker这个再来处理
			mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
				this, FieldPlayer::ATTACKER, vec_pos[i])).get());
			mPlayers.back()->placeAtPosition(mPlayers.back()->getPositionWithRegion(), BLUE_TEAM_HEADING, 0.15f);
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

