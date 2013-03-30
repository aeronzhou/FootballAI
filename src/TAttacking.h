#ifndef FOOTBALL_AI_TEAM_POSITIONAL_ATTACKING_STATE
#define FOOTBALL_AI_TEAM_POSITIONAL_ATTACKING_STATE

#include "State.h"
#include <vector>

class Team;

class Attacking : public State<Team>
{
public:
	static Attacking* get();

	void enter(Team* team);

	void execute(Team* team);

	void exit(Team* team);

	bool onMessage(Team*, const Message& msg);
};


#endif