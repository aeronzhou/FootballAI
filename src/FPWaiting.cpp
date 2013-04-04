#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "Team.h"
#include "Goal.h"
#include "MessageDispatcher.h"
#include "Constant.h"

// Waiting
Waiting* Waiting::get()
{
	static Waiting instance;
	return &instance;
}

void Waiting::enter(FieldPlayer*)
{
}

void Waiting::execute(FieldPlayer* player)
{
	// Pushed out of target 
	if (!player->isAtTarget())
	{
		player->getSteering()->setArriveOn();
	}
	else 
	{
		// Face to the ball
		player->getSteering()->setArriveOff();		
		player->setVelocity(Ogre::Vector3::ZERO);
		player->turnAroundToBall();
	}

	// If this player is more beneficial to attack
	// Ask for pass now
	if (player->getTeam()->isInControl() &&
		!player->isControllingPlayer() &&
		player->isAheadOfController())
	{
		player->getTeam()->requestPass(player);
		return;
	}

	if (player->getPitch()->isGameOn())
	{
		// Lose the ball
		// Go and catch it
		if (player->isClosestTeamMemberToBall() &&
			player->getTeam()->getReceivingPlayer() == nullptr &&
			!player->getPitch()->isGoalKeeperHasBall())
		{
			player->getStateMachine()->changeState(ChasingBall::get());
		}
	}

}

void Waiting::exit(FieldPlayer*)
{

}

bool Waiting::onMessage(FieldPlayer*, const Message&)
{
	return false;
}