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
	if (player->atTarget())
	{
		// Wait there and face to the ball
		player->getSteering()->setArriveOff();
		player->turnAroundToBall();
	}
}

void Receiving::exit(FieldPlayer* player)
{
	player->getSteering()->setArriveOff();
}

bool Receiving::onMessage(FieldPlayer*, const Message&)
{
	return false;
}