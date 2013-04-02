#ifndef FOOTBALL_AI_FIELD_PLAYER_FIND_RIGHT_PLACE
#define FOOTBALL_AI_FIELD_PLAYER_FIND_RIGHT_PLACE

#include "State.h"

class FieldPlayer;

/** 
  * Positioning State
  */
class Positioning : public State<FieldPlayer>
{
public:
	static Positioning* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif