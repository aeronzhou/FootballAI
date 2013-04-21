#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "Team.h"
#include "MessageDispatcher.h"
#include "Constant.h"


// ReturnHome
ReturnHome* ReturnHome::get()
{
	static ReturnHome instance;
	return &instance;
}

void ReturnHome::enter(GoalKeeper* keeper)
{
	keeper->getSteering()->setArriveOn();
}

void ReturnHome::execute(GoalKeeper* keeper)
{
	keeper->getSteering()->setTarget(keeper->getAssignedRegion()->getCenter());
	if(keeper->isWithinAssignedRegion() || !keeper->getTeam()->isInControl())
	{
		keeper->getStateMachine()->changeState(TendGoal::get());
	}
}

void ReturnHome::exit(GoalKeeper* keeper)
{
	keeper->getSteering()->setArriveOff();
}

bool ReturnHome::onMessage(GoalKeeper*, const Message&)
{
	return false;
}

