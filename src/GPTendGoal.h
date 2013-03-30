#ifndef FOOTBALL_AI_GOAL_KEEPER_TEND_GOAL
#define FOOTBALL_AI_GOAL_KEEPER_TEND_GOAL

#include "State.h"

class GoalKeeper;

class TendGoal : public State<GoalKeeper>
{
public:
	static TendGoal* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);

	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);

};
#endif