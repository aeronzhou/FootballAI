#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "Pitch.h"
#include "Ball.h"

InterceptBall* InterceptBall::get()
{
	static InterceptBall instance;
	return &instance;
}

void InterceptBall::enter(GoalKeeper* keeper)
{
	keeper->getSteering()->setPursuitOn();
}

void InterceptBall::execute(GoalKeeper* keeper)
{
	if (keeper->isTooFarFromGoalMouth() && !keeper->isClosestPlayerOnPitchToBall())
	{
		//keeper->getStateMachine()->changeState(ReturnHome::get());
		return;
	}

	// If the keeper can control the ball now
	if (keeper->isBallWithinControlRange())
	{
		keeper->getBall()->stop();
		keeper->getPitch()->setGoalKeeperHasBall(true);
		//keeper->getStateMachine()->changeState(PutBalBackInPlayer::get());
	}
}


void InterceptBall::exit(GoalKeeper* keeper)
{
	keeper->getSteering()->setPursuitOff();
}

bool InterceptBall::onMessage(GoalKeeper*, const Message&)
{
	return false;
}
