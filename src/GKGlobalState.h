#ifndef FOOTBALL_AI_GOAL_KEEPER_GLOBAL_STATE
#define FOOTBALL_AI_GOAL_KEEPER_GLOBAL_STATE

#include "State.h"

class GoalKeeper;

class GoalKeeperGlobalState : public State<GoalKeeper>
{
public:
	static GoalKeeperGlobalState* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);
	
	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);
};
#endif