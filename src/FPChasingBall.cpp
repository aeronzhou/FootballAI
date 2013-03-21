#include "FieldPlayerState.h"
#include "Ball.h"
#include "Team.h"

// ChasingBall
ChasingBall* ChasingBall::get()
{
	static ChasingBall instance;
	return &instance;
}

void ChasingBall::enter(FieldPlayer* player)
{
	player->getMotionAider()->seekOn();
}

void ChasingBall::execute(FieldPlayer* player)
{
	player->getMotionAider()->setTarget(player->getBall()->getPosition());

	// If the ball within kicking range
	if (player->getDistToBall() < player->getControlRange())
	{
		player->getStateMachine()->changeState(KickingBall::get());
		return;
	}

	// If the team has controlled the ball, find right place
	if (player->getTeam()->isControllingBall() && player->getTeam()->getControllingPlayer() != player)
	{
		player->getStateMachine()->changeState(FindRightPlace::get());
	}

	// If the team hasn't controlled the ball, but not proper to chase the ball

}

void ChasingBall::exit(FieldPlayer* player)
{
	player->getMotionAider()->seekOff();
}

bool ChasingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}