#ifndef FOOTBALL_AI_GOAL_KEEPER_PUT_BALL_BACKIN_PLAY_STATE
#define FOOTBALL_AI_GOAL_KEEPER_PUT_BALL_BACKIN_PLAY_STATE

#include "State.h"

class GoalKeeper;

class PutBallBackInPlayState : public State<GoalKeeper>
{
public:
	static PutBallBackInPlayState* get();

	void enter(GoalKeeper*);

	void execute(GoalKeeper*);

	void exit(GoalKeeper*);

	bool onMessage(GoalKeeper*, const Message&);
};
#endif