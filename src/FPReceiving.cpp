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
	player->getMotionAider()->setArriveOn();	
}

void Receiving::execute(FieldPlayer* player)
{
	// The ball is interuppted by others
	if (!player->getTeam()->isControllingBall())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}

	// Player arrive there
	if (player->atTarget())
	{
		// Wait there and face to the ball
		player->getMotionAider()->setArriveOff();
		player->turnAroundToBall();
	}
}

void Receiving::exit(FieldPlayer* player)
{
	player->getMotionAider()->setArriveOff();
}

bool Receiving::onMessage(FieldPlayer*, const Message&)
{
	return false;
}