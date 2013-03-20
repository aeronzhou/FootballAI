#include "FieldPlayerState.h"
#include "Team.h"

// KickingBall
KickingBall* KickingBall::get()
{
	static KickingBall instance;
	return &instance;
}

void KickingBall::enter(FieldPlayer* player)
{
	player->getTeam()->setControllingPlayer(player);
	player->getTeam()->getOpponent()->setControllingPlayer(nullptr);

	if (!player->isReadyToKick())
	{
		player->getStateMachine()->changeState(ChasingBall::get());
	}
}

void KickingBall::execute(FieldPlayer* player)
{
	// Cannot kick the ball

	// Can shoot

	// Can pass

	// Should dribble
	player->getStateMachine()->changeState(Dribbling::get());
}

void KickingBall::exit(FieldPlayer*)
{

}

bool KickingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}