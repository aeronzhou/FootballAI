#ifndef FOOTBALL_AI_FIELD_PLAYER_BACK_TO_ORIGIN_STATE
#define FOOTBALL_AI_FIELD_PLAYER_BACK_TO_ORIGIN_STATE

#include "State.h"

class FieldPlayer;

// BackToOrigin
class BackToOrigin: public State<FieldPlayer>
{
public:
	static BackToOrigin* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};


#endif