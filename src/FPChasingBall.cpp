#include "FieldPlayerState.h"
#include "Ball.h"

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

	// If within controlling area
	if (player->getDistToBall() < player->getControlRange())
	{
		player->getStateMachine()->changeState(Dribbling::get());
		//dt::Logger::get().debug("Give you a kick");
	}
}

void ChasingBall::exit(FieldPlayer* player)
{
	player->getMotionAider()->seekOff();
}

bool ChasingBall::onMessage(FieldPlayer*, const Message&)
{
	return false;
}