#ifndef FOOTBALL_AI_FIELD_PLAYER_WAITING_STATE
#define FOOTBALL_AI_FIELD_PLAYER_WAITING_STATE

#include "State.h"

class FieldPlayer;

// Waiting
class Waiting: public State<FieldPlayer>
{
public:
	static Waiting* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif