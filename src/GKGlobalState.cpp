#include "GoalKeeperState.h"
#include "GoalKeeper.h"
#include "MessageDispatcher.h"
#include "Constant.h"


GoalKeeperGlobalState* GoalKeeperGlobalState::get()
{
	static GoalKeeperGlobalState instance;
	return &instance;
}

void GoalKeeperGlobalState::enter(GoalKeeper*)
{

}

void GoalKeeperGlobalState::execute(GoalKeeper*)
{

}

void GoalKeeperGlobalState::exit(GoalKeeper*)
{

}

bool GoalKeeperGlobalState::onMessage(GoalKeeper* keeper, const Message& msg)
{
	switch (msg.msg_type)
	{
		case MSG_BACK_TO_ORIGIN:
		{
			keeper->getStateMachine()->changeState(ReturnHomeState::get());
		}
		break;

		case MSG_RECEIVE_BALL:
		{
			keeper->getStateMachine()->changeState(InterceptBall::get());
		}
	}

	return false;
}