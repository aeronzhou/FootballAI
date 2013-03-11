#ifndef FOOTBALL_AI_TEAM_STATE
#define FOOTBALL_AI_TEAM_STATE

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

class PositionalAttacking : public State<Team>
{
public:
	static PositionalAttacking* get();

	void enter(Team* team);

	void execute(Team* team);

	void exit(Team* team);

	bool onMessage(Team*, const Message& msg);
};

class PositionalDefending : public State<Team>
{
public:
	static PositionalDefending& get();

	void enter(Team* team);

	void execute(Team* team);

	void exit(Team* team);

	bool onMessage(Team*, const Message& msg);
};

#endif