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
#include "ParamLoader.h"
#include "MessageDeliverer.h"
#include "Constant.h"

Team::Team(Ball* ball, Pitch* pitch, TeamColor color, Goal* goal)
	: mBall(ball), mPitch(pitch), mColor(color), mGoal(goal), 
	  mOpponent(nullptr), mControllingPlayer(nullptr), mPlayers(std::vector<Player*>()) {}


void Team::onInitialize() 
{
	// Setup state machine
	mStateMachine = new StateMachine<Team>(this);
	mStateMachine->setCurrentState(WaitingForKickOff::get());	

	// Initialize players
	createPlayers();

	for (auto it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		// Initilize players' position, heading, etc.
		(*it)->getMotionAider()->separationOn();
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
	mStateMachine->onUpdate();	

	dt::Node::onUpdate(time_diff);
}

void Team::createPlayers()
{
	std::vector<int> vec_pos = PlayerPositionManager::get().getAssignedPosition("WaitingForKickOff");

	// Generate players with PlayerManager
	if (getTeamColor() == RED)
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(0), 
			this, FieldPlayer::FORWARD, vec_pos[0])).get());
		//for (int i = 1; i < 3; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
		//		this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		//}
		//for (int i = 3; i < 6; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(i), 
		//		this, FieldPlayer::BACK, vec_pos[i])).get());
		//}
		//mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Red_" + dt::Utils::toString(6), 
		//	this, FieldPlayer::BACK, vec_pos[6])).get());

		for (int i = 0; i < mPlayers.size(); ++i)
		{
			mPlayers[i]->placeAtPosition(mPlayers[i]->getPositionWithRegion(), RED_TEAM_HEADING, Prm.PlayerScale);
		}
	}
	else 
	{
		mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(0), 
			this, FieldPlayer::FORWARD, vec_pos[7])).get());
		//for (int i = 8; i < 10; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
		//		this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		//}
		//for (int i = 10; i < 13; ++i)
		//{
		//	mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(i - 7), 
		//		this, FieldPlayer::MIDFIELD, vec_pos[i])).get());
		//}
		//mPlayers.push_back((FieldPlayer*)addChildNode(PlayerManager::get().createFieldPlayer("Blue_" + dt::Utils::toString(6), 
		//	this, FieldPlayer::MIDFIELD, vec_pos[13])).get());

		for (int i = 0; i < mPlayers.size(); ++i)
		{
			mPlayers[i]->placeAtPosition(mPlayers[i]->getPositionWithRegion(), BLUE_TEAM_HEADING, Prm.PlayerScale);
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

void Team::playersBackForKickOff()
{
	for (int i = mPlayers.size() - 1; i >= 0; --i)
	{
		MessageDeliverer::get().deliverMessage(DELIVER_IMMEDIATELY,
			NULL, 
			mPlayers[i],
			MSG_BACK_TO_ORIGIN,
			NULL);
	}
}

bool Team::allPlayersInAssignedRegions() const 
{
	for (auto player = mPlayers.begin(); player != mPlayers.end(); ++player)
	{
		if (!(*player)->withinAssignedRegion())
		{
			return false;
		}
	}
	return true;
}

void Team::setAssignedRegion(const std::vector<int>& vec_pos)
{
	if (getTeamColor() == RED)
	{
		for (int i = mPlayers.size() - 1; i >= 0; --i)
		{
			mPlayers[i]->setAssignedRegion(vec_pos[i]);
		}
	}
	else 
	{
		for (int i = mPlayers.size() - 1; i >= 0; --i)
		{
			mPlayers[i]->setAssignedRegion(vec_pos[i + 7]);
		}
	}
}

StateMachine<Team>* Team::getStateMachine() const 
{
	return mStateMachine;
}

void Team::sendPlayersToAssignedRegion()
{
	for (std::vector<Player*>::iterator it = mPlayers.begin(); it != mPlayers.end(); ++it)
	{
		(*it)->getMotionAider()->arriveOn();
		(*it)->setTarget((*it)->getAssignedRegion()->getCenter());
	}
}
