#ifndef FOOTBALL_AI_FIELD_PLAYER_SHOOTING_STATE
#define FOOTBALL_AI_FIELD_PLAYER_SHOOTING_STATE

#include "State.h"

class FieldPlayer;

// Shooting
class Shooting: public State<FieldPlayer>
{
public:
	static Shooting* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif