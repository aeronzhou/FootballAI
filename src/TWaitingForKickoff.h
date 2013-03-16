#ifndef FOOTBALL_AI_TEAM_WAITING_FOR_KICKOFF_STATE
#define FOOTBALL_AI_TEAM_WAITING_FOR_KICKOFF_STATE

#include "State.h"
#include <vector>

class Team;

class WaitingForKickOff : public State<Team>
{
public:
	static WaitingForKickOff* get();

	void enter(Team* team);

	void execute(Team* team);

	void exit(Team* team);

	bool onMessage(Team*, const Message& msg);
};


#endif