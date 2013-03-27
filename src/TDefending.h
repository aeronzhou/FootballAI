#ifndef FOOTBALL_AI_TEAM_POSITIONAL_DEFENDING_STATE
#define FOOTBALL_AI_TEAM_POSITIONAL_DEFENDING_STATE

#include "State.h"
#include <vector>

class Team;

class Defending : public State<Team>
{
public:
	static Defending* get();

	void enter(Team* team);

	void execute(Team* team);

	void exit(Team* team);

	bool onMessage(Team*, const Message& msg);
};


#endif