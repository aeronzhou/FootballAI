#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "Team.h"
#include "MessageDispatcher.h"
#include "Constant.h"


// ReturnHomeState
ReturnHomeState* ReturnHomeState::get()
{
	static ReturnHomeState instance;
	return &instance;
}

void ReturnHomeState::enter(GoalKeeper* keeper)
{
	keeper->getSteering()->setArriveOn();
}

void ReturnHomeState::execute(GoalKeeper* keeper)
{
	keeper->getSteering()->setTarget(keeper->getAssignedRegion()->getCenter());
	if(keeper->withinAssignedRegion() || !keeper->getTeam()->isInControl())
	{
		keeper->getStateMachine()->changeState(TendGoal::get())
	}
}

void ReturnHomeState::exit(GoalKeeper* keeper)
{
	keeper->getSteering()->setArriveOff();
}

bool ReturnHomeState::onMessage(GoalKeeper*, const Message&)
{
	return false;
}

