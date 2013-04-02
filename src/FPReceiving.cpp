#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "SteeringBehaviors.h"
#include "Team.h"

Receiving* Receiving::get()
{
	static Receiving instance;
	return &instance;
}

void Receiving::enter(FieldPlayer* player)
{
	player->getSteering()->setArriveOn();	
	player->getTeam()->setReceivingPlayer(player);	

	// The player is also the controlling player
	player->getTeam()->setControllingPlayer(player);
}

void Receiving::execute(FieldPlayer* player)
{
	// The ball is interuppted by others
	if (!player->getTeam()->isInControl() || 
		player->getDistToBall() < 3 )
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}

	// Player arrive there
	if (player->isAtTarget())
	{
		// Wait there and face to the ball
		player->getSteering()->setArriveOff();
		player->turnAroundToBall();
		player->setVelocity(Ogre::Vector3::ZERO);
	}
}

void Receiving::exit(FieldPlayer* player)
{
	player->getSteering()->setArriveOff();
	player->getTeam()->setReceivingPlayer(nullptr);
}

bool Receiving::onMessage(FieldPlayer*, const Message&)
{
	return false;
}