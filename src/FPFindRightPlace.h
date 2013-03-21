#ifndef FOOTBALL_AI_FIELD_PLAYER_FIND_RIGHT_PLACE
#define FOOTBALL_AI_FIELD_PLAYER_FIND_RIGHT_PLACE

#include "State.h"

class FieldPlayer;

/** 
  * FindRightPlace State
  */
class FindRightPlace : public State<FieldPlayer>
{
public:
	static FindRightPlace* get();

	void enter(FieldPlayer*);

	void execute(FieldPlayer*);

	void exit(FieldPlayer*);

	bool onMessage(FieldPlayer*, const Message&);
};

#endif