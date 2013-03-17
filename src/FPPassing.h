#ifndef FOOTBALL_AI_FIELD_PLAYER_PASSING_STATE
#define FOOTBALL_AI_FIELD_PLAYER_PASSING_STATE

#include "State.h"

class FieldPlayer;

// Passing
class Passing: public State<FieldPlayer>
{
public:
	static Passing* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif