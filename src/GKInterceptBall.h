#ifndef FOOTBALL_AI_GOAL_KEEPER_INTERCEPT_BALL
#define FOOTBALL_AI_GOAL_KEEPER_INTERCEPT_BALL

#include "State.h"

class GoalKeeper;

class InterceptBall : public State<GoalKeeper>
{
public:
	static InterceptBall* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);

	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);
};

#endif