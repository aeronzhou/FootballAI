#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "MotionAider.h"
#include "Team.h"

Receiving* Receiving::get()
{
	static Receiving instance;
	return &instance;
}

void Receiving::enter(FieldPlayer* player)
{
	player->getMotionAider()->arriveOn();	
}

void Receiving::execute(FieldPlayer* player)
{
	// The ball is interuppted by others
	if (!player->getTeam()->isControllingBall())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}
}

void Receiving::exit(FieldPlayer* player)
{
	player->getMotionAider()->arriveOff();
}

bool Receiving::onMessage(FieldPlayer*, const Message&)
{
	return false;
}