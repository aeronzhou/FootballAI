#ifndef FOOTBALL_AI_FIELD_PLAYER_GLOBAL_STATE
#define FOOTBALL_AI_FIELD_PLAYER_GLOBAL_STATE

#include "State.h"
#include "FieldPlayer.h"

//class FieldPlayer; 

// FieldPlayerGlobalState
class FieldPlayerGlobalState: public State<FieldPlayer>
{
public:
	static FieldPlayerGlobalState* get();

	void enter(FieldPlayer*) {}

	void execute(FieldPlayer*) {}

	void exit(FieldPlayer*) {}

	bool onMessage(FieldPlayer*, const Message&);
};


#endif