#ifndef FOOTBALL_AI_FIELD_PLAYER_SUPPORT_ATTACKER
#define FOOTBALL_AI_FIELD_PLAYER_SUPPORT_ATTACKER

#include "State.h"

class FieldPlayer;

class SupportAttacker : public State<FieldPlayer>
{
public:
	static SupportAttacker* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif