#ifndef FOOTBALL_AI_GOAL_KEEPER_RETURN_HOME_STATE
#define FOOTBALL_AI_GOAL_KEEPER_RETURN_HOME_STATE

#include "State.h"

class GoalKeeper;

// ReturnHomeState
class ReturnHomeState: public State<GoalKeeper>
{
public:
	static ReturnHomeState* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);

	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);
};


#endif