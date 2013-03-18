#include "FieldPlayerState.h"
#include "FieldPlayer.h"
#include "Team.h"
#include "MessageDeliverer.h"
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
	// If game is not started, don't respond
	//////////////////////////////////////////////////////////////////////////

	// Ball coming or closest to the ball, chase it
	if (player == (FieldPlayer*)player->getTeam()->getPlayerClosestToBall())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}
}

void Waiting::exit(FieldPlayer*)
{

}

bool Waiting::onMessage(FieldPlayer*, const Message&)
{
	return false;
}