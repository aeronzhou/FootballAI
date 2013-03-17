#ifndef FOOTBALL_AI_FIELD_PLAYER_DRIBBLING_STATE
#define FOOTBALL_AI_FIELD_PLAYER_DRIBBLING_STATE

#include "State.h"

class FieldPlayer;

// Dribbling
class Dribbling: public State<FieldPlayer>
{
public:
	static Dribbling* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif