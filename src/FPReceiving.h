#ifndef FOOTBALL_AI_FIELD_PLAYER_RECEIVING
#define FOOTBALL_AI_FIELD_PLAYER_RECEIVING

#include "State.h"

class FieldPlayer;

class Receiving : public State<FieldPlayer>
{
public:
	static Receiving* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif