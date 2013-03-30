#include "GoalKeeperState.h"

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

bool GoalKeeperGlobalState::onMessage(GoalKeeper*, const Message&)
{
	return false;
}