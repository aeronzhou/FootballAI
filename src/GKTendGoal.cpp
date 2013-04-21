#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "Pitch.h"
#include "Team.h"
#include "Ball.h"

TendGoal* TendGoal::get()
{
	static TendGoal instance;
	return &instance;
}

void TendGoal::enter(GoalKeeper* keeper)
{
	keeper->getSteering()->setInterposeOn();
	keeper->setTarget(keeper->getRearInterposeTarget());
}

void TendGoal::execute(GoalKeeper* keeper)
{
	keeper->setTarget(keeper->getRearInterposeTarget());


	if (keeper->isBallWithinControlRange())
	{
		keeper->getBall()->stop();
		keeper->getPitch()->setGoalKeeperHasBall(true);
		keeper->getStateMachine()->changeState(PutBallBackInPlayState::get());
		return;
	}

	// If the ball is within intercept range, catch it
	if (keeper->isBallWithInterceptRange() && !keeper->getTeam()->isInControl())
	{
		keeper->getStateMachine()->changeState(InterceptBall::get());
		return;
	}

	if (keeper->isTooFarFromGoalMouth() && keeper->getTeam()->isInControl())
	{
		keeper->getStateMachine()->changeState(ReturnHome::get());
	}
}

void TendGoal::exit(GoalKeeper* keeper)
{
	keeper->getSteering()->setInterposeOff();
}

bool TendGoal::onMessage(GoalKeeper*, const Message&)
{
	return false;
}