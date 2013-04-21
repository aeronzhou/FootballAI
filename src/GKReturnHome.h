#ifndef FOOTBALL_AI_GOAL_KEEPER_RETURN_HOME_STATE
#define FOOTBALL_AI_GOAL_KEEPER_RETURN_HOME_STATE

#include "State.h"

class GoalKeeper;

// ReturnHome
class ReturnHome: public State<GoalKeeper>
{
public:
	static ReturnHome* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);

	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);
};


#endif